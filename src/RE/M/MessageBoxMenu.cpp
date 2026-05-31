#include "RE/M/MessageBoxMenu.h"

#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMessageBoxCallback.h"
#include "RE/M/MessageBoxData.h"
#include "RE/U/UIMessage.h"
#include "RE/U/UIMessageQueue.h"

namespace RE
{
	MessageBoxMenu* MessageBoxMenu::GetCurrentMessageBoxMenu()
	{
		static REL::Relocation<MessageBoxMenu**> menu{ RELOCATION_ID(0, 406361) };
		return *menu;
	}

	std::uint32_t MessageBoxMenu::GetQueueSize()
	{
		static REL::Relocation<BSTArray<MessageBoxData*>*> queue{ RELOCATION_ID(519818, 406360) };
		return queue->size();
	}

	void MessageBoxMenu::QueueMessage(MessageBoxData* a_data)
	{
		using func_t = decltype(&MessageBoxMenu::QueueMessage);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51422, 52271) };
		return func(a_data);
	}

	MessageBoxData* MessageBoxMenu::GetCurrentMessageBoxData()
	{
		static REL::Relocation<BSTArray<MessageBoxData*>*> queue{ RELOCATION_ID(519818, 406360) };
		return queue->empty() ? nullptr : queue->back();
	}

	void MessageBoxMenu::RemoveMessageFromQueue(MessageBoxData* a_data)
	{
		// Engine ABI: (MessageBoxMenu* a_menu, MessageBoxData* a_data). The menu 'this' is ignored
		// (the queue is a global), so nullptr is safe. Finds a_data in the queue, removes it, and
		// runs its scalar-deleting destructor.
		using func_t = void (*)(MessageBoxMenu*, MessageBoxData*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51426, 52284) };
		func(nullptr, a_data);
	}

	void MessageBoxMenu::SelectOption(std::int32_t a_buttonIndex)
	{
		static REL::Relocation<BSTArray<MessageBoxData*>*> queue{ RELOCATION_ID(519818, 406360) };
		if (queue->empty()) {
			return;
		}

		auto* data = queue->back();
		// Hold a ref so the callback survives RemoveMessageFromQueue destroying `data`.
		BSTSmartPointer<IMessageBoxCallback> callback = data->callback;
		const auto                           option = static_cast<IMessageBoxCallback::Message>(data->optionIndexOffset + a_buttonIndex);

		RemoveMessageFromQueue(data);

		// No SWF is driving the close, so hide the menu ourselves once nothing else is queued.
		if (queue->empty()) {
			if (auto* uiQueue = UIMessageQueue::GetSingleton()) {
				uiQueue->AddMessage(MENU_NAME.data(), UI_MESSAGE_TYPE::kHide, nullptr);
			}
		}

		if (callback) {
			callback->Run(option);
		}
	}
}
