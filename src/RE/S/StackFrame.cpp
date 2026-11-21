#include "RE/S/StackFrame.h"

#include "RE/I/IFunction.h"
#include "RE/O/ObjectTypeInfo.h"
#include "RE/S/Stack.h"

namespace RE
{
	namespace BSScript
	{
		StackFrame::StackFrame(Stack* a_stack, const std::uint32_t a_frameSize) :
			parent(a_stack), size(a_frameSize)
		{
			previousFrame = nullptr;
			instructionPointer = 0;
			instructionsValid = true;

			const auto pageHint = GetPageForFrame();
			for (std::uint32_t i = 0; i < a_frameSize; ++i) {
				std::construct_at(std::addressof(GetStackFrameVariable(i, pageHint)));
			}
		}

		StackFrame::~StackFrame()
		{
			const auto pageHint = GetPageForFrame();
			for (std::uint32_t i = 0; i < size; ++i) {
				GetStackFrameVariable(i, pageHint) = Variable();
			}
		}

		std::uint32_t StackFrame::GetPageForFrame() const
		{
			return parent->GetPageForFrame(this);
		}

		Variable& StackFrame::GetStackFrameVariable(std::uint32_t a_index, std::uint32_t a_pageHint) const
		{
			return parent->GetStackFrameVariable(this, a_index, a_pageHint);
		}

		bool StackFrame::InitFrame(BSTSmartPointer<IFunction>& a_function, const BSTSmartPointer<ObjectTypeInfo>& a_type, const Variable& a_self, const BSScrapArray<Variable>& a_args)
		{
			owningFunction = a_function;
			owningObjectType = a_type;
			self = a_self;

			const auto pageHint = parent->GetPageForFrame(this);

			bool ok = true;
			for (std::uint32_t i = 0; i < a_args.size(); ++i) {
				ok = i < size;
				if (ok) {
					parent->GetStackFrameVariable(this, i, pageHint) = a_args[i];
				}
			}

			if (ok) {
				a_function->InsertLocals(this);
			}
			return ok;
		}
	}
}