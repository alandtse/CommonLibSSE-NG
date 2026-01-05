#include "RE/M/MessageBoxMenu.h"

#include "RE/B/BSTArray.h"
#include "RE/M/MessageBoxData.h"

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
}
