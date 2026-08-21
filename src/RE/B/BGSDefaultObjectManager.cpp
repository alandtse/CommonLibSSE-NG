#include "RE/B/BGSDefaultObjectManager.h"

#include "SKSE/Version.h"

using namespace REL;

namespace RE
{
	namespace
	{
		constexpr auto kInvalid = (std::numeric_limits<std::size_t>::max)();

		// AE 1.7.99 inserts 6 new entries into objects[]/objectInit[] (1 before
		// index 188, 5 more before 263), growing the array from 364 to 372.
		inline bool IsAe1799() noexcept
		{
#ifdef ENABLE_SKYRIM_AE
			if SKYRIM_REL_CONSTEXPR (Module::IsAE()) {
				return Module::get().version().compare(SKSE::RUNTIME_SSE_1_7_99) != std::strong_ordering::less;
			}
#endif
			return false;
		}

		inline std::size_t MapIndex(std::underlying_type_t<DefaultObjectID> a_idx) noexcept
		{
			if (a_idx <= std::to_underlying(DefaultObjectID::kKeywordActivatorFurnitureNoPlayer)) {
				return a_idx;
			}
			std::size_t result;
			if SKYRIM_REL_CONSTEXPR (Module::IsVR()) {
				result = (0xFFFF0000 & a_idx) >> 16;
			} else {
				result = 0x0000FFFF & a_idx;
				if (IsAe1799()) {
					if (result >= 263) {
						result += 6;
					} else if (result >= 188) {
						result += 1;
					}
				}
			}
			return result ? result : kInvalid;
		}
	}

	TESForm** BGSDefaultObjectManager::GetObject(DefaultObjectID a_object) noexcept
	{
		auto idx = MapIndex(std::to_underlying(a_object));
		if (idx == kInvalid) {
			return nullptr;
		}
		assert(idx < static_cast<std::size_t>(IsAe1799() ? 372 : Relocate(364, 364, 369)));
		return IsObjectInitialized(idx) ?
		           &(&RelocateMember<TESForm*>(this, 0x20, 0x20))[idx] :
		           nullptr;
	}

	bool BGSDefaultObjectManager::IsObjectInitialized(DefaultObjectID a_object) const noexcept
	{
		return IsObjectInitialized(MapIndex(std::to_underlying(a_object)));
	}

	bool BGSDefaultObjectManager::IsObjectInitialized(std::size_t a_idx) const noexcept
	{
		const std::uintptr_t objectInitOffset = IsAe1799() ? 0xBC0 : 0xB80;
		return (&RelocateMember<bool>(this, objectInitOffset, 0xBA8))[a_idx];
	}

	TESForm** BGSDefaultObjectManager::GetAe1799Object(Ae1799Object a_object) noexcept
	{
		if (!IsAe1799()) {
			return nullptr;
		}
		const auto idx = std::to_underlying(a_object);
		return IsObjectInitialized(idx) ?
		           &(&RelocateMember<TESForm*>(this, 0x20, 0x20))[idx] :
		           nullptr;
	}

	bool BGSDefaultObjectManager::SupportsVR(DefaultObjectID a_object) noexcept
	{
		auto idx = std::to_underlying(a_object);
		return idx <= std::to_underlying(DefaultObjectID::kKeywordActivatorFurnitureNoPlayer) || idx & 0xFFFF0000;
	}

	bool BGSDefaultObjectManager::SupportsSE(DefaultObjectID a_object) noexcept
	{
		return (std::to_underlying(a_object) & 0x0000FFFF) || a_object != DefaultObjectID::kWerewolfSpell;
	}

	bool BGSDefaultObjectManager::SupportsCurrentRuntime(DefaultObjectID a_object) noexcept
	{
		return MapIndex(std::to_underlying(a_object)) != kInvalid;
	}
}
