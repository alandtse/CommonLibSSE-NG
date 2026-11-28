#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class ActorState;
	class BSPathingRequest;
	struct BSPathingSolution;

	// built per update by the path follower agent and passed to the path follower actions
	struct PathFollowerStateUpdateData
	{
	public:
		// members
		NiPoint3           position;          // 00
		NiPoint3           angle;             // 0C
		BSPathingRequest*  request;           // 18 - NiPointer
		BSPathingSolution* solution;          // 20 - NiPointer
		ActorState*        actorState;        // 28
		void*              messageInterface;  // 30
		NiPoint3*          pathPoint;         // 38
		float              pathPosition;      // 40
		float              deltaTime;         // 44
	};
	static_assert(sizeof(PathFollowerStateUpdateData) == 0x48);
}
