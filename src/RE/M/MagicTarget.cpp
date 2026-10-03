#include "RE/M/MagicTarget.h"

#include "RE/A/ActiveEffect.h"
#include "RE/A/Actor.h"
#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTList.h"
#include "RE/E/EffectSetting.h"
#include "RE/F/FormTraits.h"

namespace RE
{
	bool MagicTarget::DispelEffect(MagicItem* a_spell, BSPointerHandle<Actor>& a_caster, ActiveEffect* a_effect)
	{
		using func_t = decltype(&MagicTarget::DispelEffect);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33721, 34505) };
		return func(this, a_spell, a_caster, a_effect);
	}

#if !defined(EXCLUSIVE_SKYRIM_FLAT)
	BSSimpleList<ActiveEffect*>* MagicTarget::GetActiveEffectList()
	{
#	if defined(ENABLE_SKYRIM_VR)
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			// VR's slot 07 is a BSLocklessSimpleList<ActiveEffect*>: build a thread-local BSSimpleList snapshot from it
			static thread_local std::vector<ActiveEffect*>  effectsVec{};
			static thread_local BSSimpleList<ActiveEffect*> activeEffects{};

			effectsVec.clear();
			activeEffects.clear();

			if (auto list = GetVRActiveEffectList()) {
				list->ForEach([&](ActiveEffect* ae) {
					if (ae) {
						effectsVec.push_back(ae);
					}
					return BSContainer::ForEachResult::kContinue;
				});
			}

			for (auto it = effectsVec.rbegin(); it != effectsVec.rend(); ++it) {
				activeEffects.push_front(*it);
			}

			return &activeEffects;
		}
#	endif
		return static_cast<BSSimpleList<ActiveEffect*>*>(GetActiveEffectListNative());
	}
#endif

#if defined(ENABLE_SKYRIM_VR)
	BSLocklessSimpleList<ActiveEffect*>* MagicTarget::GetVRActiveEffectList()
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			return static_cast<BSLocklessSimpleList<ActiveEffect*>*>(GetActiveEffectListNative());
		} else {
			return nullptr;
		}
	}
#endif

#if defined(ENABLE_SKYRIM_VR)
	void MagicTarget::DispelEffectsWithArchetype(Archetype a_type, bool a_force)
	{
		std::vector<RE::ActiveEffect*> queued;
		VisitActiveEffects([&](ActiveEffect* effect) {
			const auto setting = effect ? effect->GetBaseObject() : nullptr;
			if (setting && setting->HasArchetype(a_type)) {
				queued.push_back(effect);
			}
			return BSContainer::ForEachResult::kContinue;
		});

		for (const auto& effect : queued) {
			effect->Dispel(a_force);
		}
	}
#endif

	// this is a base subobject at a runtime-dependent offset in Actor; a cast cannot
	// recover the actor, the object's own override does.
	Actor* MagicTarget::GetTargetAsActor()
	{
		const auto ref = GetTargetStatsObject();
		return ref ? ref->As<Actor>() : nullptr;
	}

	bool MagicTarget::HasEffectWithArchetype(Archetype a_type)
	{
		auto effects = GetActiveEffectList();
		if (!effects) {
			return false;
		}

		EffectSetting* setting = nullptr;
		for (auto& effect : *effects) {
			setting = effect ? effect->GetBaseObject() : nullptr;
			if (setting && setting->HasArchetype(a_type)) {
				return true;
			}
		}
		return false;
	}

	bool MagicTarget::HasMagicEffect(EffectSetting* a_effect)
	{
		using func_t = decltype(&MagicTarget::HasMagicEffect);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33733, 34517) };
		return func(this, a_effect);
	}

	bool MagicTarget::HasMagicEffectWithKeyword(BGSKeyword* a_keyword, MagicItem** a_spellOut)
	{
		using func_t = decltype(&MagicTarget::HasMagicEffectWithKeyword);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33734, 34518) };
		return func(this, a_keyword, a_spellOut);
	}

	void MagicTarget::VisitEffects(ForEachActiveEffectVisitor& visitor)
	{
		using func_t = decltype(&MagicTarget::VisitEffects);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33756, 34540) };
		return func(this, visitor);
	}
}
