#pragma once

namespace RE
{
	template <class Agent, class Data>
	class IMovementAgentDataTracker
	{
	public:
		virtual ~IMovementAgentDataTracker() = default;  // 00

		// add
		virtual void Track(Agent* a_agent, const Data* a_data) = 0;  // 01
	};
}
