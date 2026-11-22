#include "RE/S/Stack.h"

#include "RE/C/CodeTasklet.h"
#include "RE/I/IFunction.h"
#include "RE/I/IMemoryPagePolicy.h"
#include "RE/I/IProfilePolicy.h"
#include "RE/I/IStackCallbackFunctor.h"
#include "RE/S/StackFrame.h"

namespace RE
{
	namespace BSScript
	{
		Stack::Stack(IMemoryPagePolicy* a_memoryPagePolicy, IProfilePolicy* a_profilePolicy, VMStackID a_stackID, StackType a_type, BSTSmartPointer<IStackCallbackFunctor>& a_callback) :
			policy(a_memoryPagePolicy), profilePolicy(a_profilePolicy), returnValue(Variable()), stackID(a_stackID), stackType(a_type), owningTasklet(nullptr), callback(a_callback), nextStack(nullptr)
		{
			frames = 0;
			top = nullptr;
			state = State::kRunning;
			freezeState = FreezeState::kUnfrozen;
		}

		Stack::~Stack()
		{
			while (PopFrame()) {}
		}

		std::uint32_t Stack::GetPageForFrame(const StackFrame* a_frame) const
		{
			for (std::uint32_t i = 0; i < pages.size(); ++i) {
				auto& pair = pages[i];
				if (pair.page->IsInRange(a_frame)) {
					return i;
				}
			}
			assert(false);
			return static_cast<std::uint32_t>(-1);
		}

		Variable& Stack::GetStackFrameVariable(const StackFrame* a_frame, std::uint32_t a_index, std::uint32_t a_pageHint)
		{
			using func_t = decltype(&Stack::GetStackFrameVariable);
			static REL::Relocation<func_t> func{ RELOCATION_ID(97746, 104484) };
			return func(this, a_frame, a_index, a_pageHint);
		}

		IMemoryPagePolicy::AllocationStatus Stack::PushFrame(BSTSmartPointer<IFunction>& a_function, BSTSmartPointer<ObjectTypeInfo>& a_type, Variable& a_functionSelf, BSScrapArray<Variable>& a_args)
		{
			using Status = IMemoryPagePolicy::AllocationStatus;

			if (!a_function || !a_type) {
				return Status::kFailed;
			}

			const auto frameSize = a_function->GetStackFrameSize();
			if (a_args.size() > frameSize) {
				return Status::kFailed;
			}

			const auto result = PushBlankFrame(frameSize, false);
			if (result != Status::kSuccess || !top) {
				return result;  // a null top after a successful push also returns the (success) result, as in the original
			}

			if (profilePolicy) {
				profilePolicy->StackFramePushed(stackID, frames - 1, a_functionSelf, a_function->GetObjectTypeName(), a_function->GetStateName(), a_function->GetName());
			}

			if (top->InitFrame(a_function, a_type, a_functionSelf, a_args)) {
				return result;
			}

			PopFrame();
			return Status::kFailed;
		}

		IMemoryPagePolicy::AllocationStatus Stack::PushBlankFrame(std::uint32_t a_frameSize, bool a_ignoreMemoryLimit)
		{
			using Status = IMemoryPagePolicy::AllocationStatus;
			using Strategy = IMemoryPagePolicy::NewPageStrategy;

			const auto strategy = a_ignoreMemoryLimit ? Strategy::kIgnoreMemoryLimit : Strategy::kNormal;

			const std::uint32_t originalPageCount = pages.size();
			const std::uint32_t originalAvailable = originalPageCount != 0 ? pages.back().availableMemoryInBytes : 0;

			// a failure of GetLargestAvailablePage maps to kFailed or kOutOfMemory; the status of the first AllocatePage failure is ignored
			const auto failedResult = [](Status a_status) {
				return a_status == Status::kFailed ? Status::kFailed : Status::kOutOfMemory;
			};

			Status        result = Status::kSuccess;
			char*         frameMemory = nullptr;
			std::uint32_t available = originalAvailable;

			if (available >= 0x40) {
				auto* page = pages.back().page.get();
				frameMemory = reinterpret_cast<char*>(page) + 4 + (page->pageSize - available);
				available -= 0x40;
				pages.back().availableMemoryInBytes = available;
			} else {
				BSTAutoPointer<MemoryPage> page;
				bool                       usePage = policy->AllocatePage((a_frameSize + 4) << 4, strategy, page) == Status::kSuccess;
				if (!usePage) {
					const auto largest = policy->GetLargestAvailablePage(page);
					if (largest != Status::kSuccess) {
						result = failedResult(largest);
					} else if (page->pageSize >= 0x40) {
						usePage = true;
					} else {
						policy->DisposePage(page);
						result = Status::kOutOfMemory;
					}
				}

				if (usePage) {
					available = page->pageSize - 0x40;
					frameMemory = reinterpret_cast<char*>(page.get()) + 4;
					pages.push_back(Stack::MemoryPageData{ std::move(page), available, 0 });  // sub_141247310
				}
			}

			if (result == Status::kSuccess) {
				// the header page also holds as many of the frame's variables as fit; the rest spreads over further pages
				const std::uint32_t here = std::min(a_frameSize, available >> 4);
				pages.back().availableMemoryInBytes = available - (here << 4);

				std::uint32_t remaining = a_frameSize - here;
				while (remaining != 0 && result == Status::kSuccess) {
					BSTAutoPointer<MemoryPage> page;
					if (policy->AllocatePage(remaining << 4, strategy, page) == Status::kSuccess) {
						const auto left = page->pageSize - (remaining << 4);
						pages.push_back(Stack::MemoryPageData{ std::move(page), left, 0 });
						remaining = 0;
						continue;
					}

					const auto largest = policy->GetLargestAvailablePage(page);
					if (largest != Status::kSuccess) {
						result = failedResult(largest);
					} else if (page->pageSize >= 0x10) {
						const std::uint32_t take = std::min(remaining, page->pageSize >> 4);
						remaining -= take;
						const auto left = page->pageSize - (take << 4);
						pages.push_back(Stack::MemoryPageData{ std::move(page), left, 0 });
					} else {
						policy->DisposePage(page);
						result = Status::kOutOfMemory;
					}
				}
			}

			if (result == Status::kSuccess) {
				auto* frame = new (frameMemory) StackFrame(this, a_frameSize);
				frame->previousFrame = top;
				top = frame;
				frames += 1;
				return result;
			}

			// roll back: give back every page this call added and restore the page that was there before
			while (pages.size() > originalPageCount) {
				policy->DisposePage(pages.back().page);
				pages.pop_back();  // frees the page if the policy did not take it
			}
			if (pages.size() != 0) {
				pages.back().availableMemoryInBytes = originalAvailable;
			}
			return result;
		}

		bool Stack::PopFrame()
		{
			if (frames == 0 || pages.empty() || !top) {
				return false;
			}

			if (profilePolicy) {
				// holds a reference to the function across the call; a frame without a function is not reported
				if (const BSTSmartPointer<IFunction> function = top->owningFunction; function) {
					profilePolicy->StackFramePopped(stackID, frames - 1, top->self, function->GetObjectTypeName(), function->GetStateName(), function->GetName());
				}
			}

			auto* frame = top;
			top = frame->previousFrame;
			std::uint32_t keptBytes = (frame->size + 4) << 4;  // read before the teardown
			frame->~StackFrame();

			std::uint32_t pageIndex = GetPageForFrame(frame);
			if (frame != pages[pageIndex].page->GetHead()) {
				pageIndex += 1;
			}

			// every page from pageIndex on is given back; its used bytes are not part of what stays in the kept page
			while (pages.size() > pageIndex) {
				auto& entry = pages.back();
				keptBytes += entry.availableMemoryInBytes - entry.page->pageSize;  // before DisposePage zeroes pageSize
				policy->DisposePage(entry.page);
				pages.pop_back();
			}

			if (keptBytes != 0 && pageIndex != 0) {
				std::memset((void*)frame, 0, keptBytes);
				pages[pageIndex - 1].availableMemoryInBytes += keptBytes;
			}

			frames -= 1;
			return true;
		}
	}
}