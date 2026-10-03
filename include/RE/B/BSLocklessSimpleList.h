#pragma once

#include "RE/B/BSContainer.h"

namespace RE
{
	// Skyrim VR only (SE/AE use BSSimpleList for the same data). The head is a shared_ptr to a
	// sentinel node whose `next` is the first element; nodes are make_shared blocks and removal
	// only sets `removed`, so a walk must skip removed nodes. The engine mutates the list under
	// its own synchronisation; do not modify it from plugin code.
	template <class T>
	class BSLocklessSimpleList
	{
	public:
		struct Node
		{
			T                     item;      // 00
			std::shared_ptr<Node> next;      // 08
			bool                  removed;   // 18
			std::uint8_t          pad19[7];  // 19
		};

		// a_func: BSContainer::ForEachResult(T&)
		template <class F>
		void ForEach(F&& a_func)
		{
			if (!head) {
				return;
			}
			// Copy each link, as the engine's own walk does, so a node another thread unlinks stays
			// alive while we read it.
			for (auto node = head->next; node; node = node->next) {
				if (!node->removed && a_func(node->item) == BSContainer::ForEachResult::kStop) {
					return;
				}
			}
		}

		// members
		std::shared_ptr<Node> head;  // 00 - sentinel
	};
}
