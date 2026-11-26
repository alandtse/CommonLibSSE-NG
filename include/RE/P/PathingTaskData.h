#pragma once

#include "RE/B/BSPathingLocation.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSTaskletData.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSPathingRequest;
	struct BSPathingSolution;
	struct PathingSolutionQueue;

	// 0x20-byte records parallel to the location requests
	struct PathingTaskLocationResult
	{
	public:
		// members
		std::uint32_t               type;       // 00 - 2 = ray cast
		std::uint32_t               status;     // 04 - 0 pending, 1 ready
		BSTArray<BSPathingLocation> locations;  // 08
	};
	static_assert(sizeof(PathingTaskLocationResult) == 0x20);

	class PathingTaskData : public BSTaskletData
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingTaskData;
		inline static constexpr auto VTABLE = VTABLE_PathingTaskData;

		~PathingTaskData() override;  // 00

		// override (BSTaskletData)
		void Process() override;  // 02 - runs the registered path builder and queues the solution

		// members
		std::uint64_t                         unk10;             // 10
		std::uint8_t                          unk18;             // 18
		std::uint8_t                          pad19[3];          // 19
		std::uint32_t                         unk1C;             // 1C
		std::uint8_t                          pad20[8];          // 20
		std::int32_t                          refCount;          // 28
		std::uint32_t                         pad2C;             // 2C
		NiPointer<BSPathingRequest>           request;           // 30
		BSPathingSolution*                    solution;          // 38 - built by Process
		void*                                 result;            // 40 - owned, deleted through the vtable
		std::uint8_t                          requestLock[8];    // 48 - mutex guarding both arrays
		BSTArray<void*>                       locationRequests;  // 50 - 0x88-byte records
		BSTArray<PathingTaskLocationResult>   locationResults;   // 68 - parallel to the requests
		BSTSmartPointer<PathingSolutionQueue> solutionQueue;     // 80
		bool                                  raycastsPending;   // 88
		bool                                  buildRequested;    // 89
		std::uint8_t                          pad8A[6];          // 8A
	};
	static_assert(sizeof(PathingTaskData) == 0x90);
}
