#include "RE/C/CombatBehaviorTreeNodeObject.h"

#include "RE/C/CombatBehaviorChildSelector.h"
#include "RE/C/CombatBehaviorContextAcquireWeapon.h"
#include "RE/C/CombatBehaviorContextCloseMovement.h"
#include "RE/C/CombatBehaviorContextMagic.h"
#include "RE/C/CombatBehaviorContextMelee.h"
#include "RE/C/CombatBehaviorEquipContext.h"
#include "RE/C/CombatBehaviorFallbackSelector.h"
#include "RE/C/CombatBehaviorParallel.h"
#include "RE/C/CombatBehaviorRepeat.h"
#include "RE/C/CombatBehaviorTreeCreateContextNode.h"

// TODO remove?
namespace RE
{
	template class CombatBehaviorTreeNodeObject<CombatBehaviorRepeat>;
	template class CombatBehaviorTreeNodeObject<CombatBehaviorParallel>;
	//template class CombatBehaviorTreeNodeObject<CombatBehaviorAcquireResource>;

	template class CombatBehaviorTreeCreateContextNode<CombatBehaviorContextAcquireWeapon>;
	template class CombatBehaviorTreeCreateContextNode<CombatBehaviorContextMelee>;
	template class CombatBehaviorTreeCreateContextNode<CombatBehaviorEquipContext>;
	//template class CombatBehaviorTreeCreateContextNode<CombatBehaviorContextMagic>;

	template class CombatBehaviorChildSelector<ValueChildSelector>;
	static_assert(sizeof(CombatBehaviorChildSelector<ValueChildSelector>) == 0x4);
	template class CombatBehaviorTreeNodeObject<CombatBehaviorChildSelector<ValueChildSelector>>;
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorChildSelector<ValueChildSelector>>) == 0x28);

	template class CombatBehaviorChildSelector<RandomValueChildSelector>;
	static_assert(sizeof(CombatBehaviorChildSelector<RandomValueChildSelector>) == 0x8);
	template class CombatBehaviorTreeNodeObject<CombatBehaviorChildSelector<RandomValueChildSelector>>;
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorChildSelector<RandomValueChildSelector>>) == 0x28);

	template class CombatBehaviorChildSelector<ConditionalChildSelector>;
	static_assert(sizeof(CombatBehaviorChildSelector<ConditionalChildSelector>) == 0x4);
	template class CombatBehaviorTreeNodeObject<CombatBehaviorChildSelector<ConditionalChildSelector>>;
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorChildSelector<ConditionalChildSelector>>) == 0x28);

	template class CombatBehaviorFallbackSelector<NextChildSelector>;
	static_assert(sizeof(CombatBehaviorFallbackSelector<NextChildSelector>) == 0x8);
	template class CombatBehaviorTreeNodeObject<CombatBehaviorFallbackSelector<NextChildSelector>>;
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorFallbackSelector<NextChildSelector>>) == 0x28);

	template class CombatBehaviorFallbackSelector<WeightedRandomChildSelector>;
	static_assert(sizeof(CombatBehaviorFallbackSelector<WeightedRandomChildSelector>) == 0xC);
	template class CombatBehaviorTreeNodeObject<CombatBehaviorFallbackSelector<WeightedRandomChildSelector>>;
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorFallbackSelector<WeightedRandomChildSelector>>) == 0x28);
}
