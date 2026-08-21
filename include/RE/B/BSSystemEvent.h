#pragma once

namespace RE
{
	// Pre-existing class (predates AE 1.7.99); fields not yet reverse-engineered.
	// 1.7.99 is new only in that PlayerCharacter/SkyrimVM gain new
	// BSTEventSink<BSSystemEvent> bases -- this class itself is unchanged.
	class BSSystemEvent
	{
	public:
		std::uint64_t unk00;
		std::uint64_t unk08;
		std::uint32_t unk10;
	};
	static_assert(sizeof(BSSystemEvent) == 0x18);
}
