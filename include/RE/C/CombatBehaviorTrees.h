#pragma once

#include "RE/C/CombatBehaviorTree.h"

namespace RE
{
	class CombatBehaviorTreeCombat : public CombatBehaviorTree
	{
	public:
		static CombatBehaviorTreeCombat* GetSingleton()
		{
			REL::Relocation<CombatBehaviorTreeCombat*> singleton{ REL::ID(518752) };  
			return singleton.get();
		}

		void Initialize() override;
	};

	class CombatBehaviorTreeMovement : public CombatBehaviorTree
	{
	public:
		static CombatBehaviorTreeMovement* GetSingleton()
		{
			REL::Relocation<CombatBehaviorTreeMovement*> singleton{ REL::ID(519075) };  
			return singleton.get();
		}

		void Initialize() override;
	};

	class CombatBehaviorTreeAcquireWeapon : public CombatBehaviorTree
	{
	public:
		static CombatBehaviorTreeAcquireWeapon* GetSingleton()
		{
			REL::Relocation<CombatBehaviorTreeAcquireWeapon*> singleton{ REL::ID(518759) };  
			return singleton.get();
		}

		void Initialize() override;
	};

	class CombatBehaviorTreeAction : public CombatBehaviorTree
	{
	public:
		static CombatBehaviorTreeAction* GetSingleton()
		{
			REL::Relocation<CombatBehaviorTreeAction*> singleton{ REL::ID(518776) };  
			return singleton.get();
		}

		void Initialize() override;
	};

	class CombatBehaviorTreeActionEquipmentSelector : public CombatBehaviorTree
	{
	public:
		static CombatBehaviorTreeActionEquipmentSelector* GetSingleton()
		{
			REL::Relocation<CombatBehaviorTreeActionEquipmentSelector*> singleton{ REL::ID(518777) };  
			return singleton.get();
		}

		void Initialize() override;
	};

	class CombatBehaviorTreeDodgeThreat : public CombatBehaviorTree
	{
	public:
		static CombatBehaviorTreeDodgeThreat* GetSingleton()
		{
			REL::Relocation<CombatBehaviorTreeDodgeThreat*> singleton{ REL::ID(518800) };  
			return singleton.get();
		}

		void Initialize() override;
	};

	class CombatBehaviorTreeBlock : public CombatBehaviorTree
	{
	public:
		static CombatBehaviorTreeBlock* GetSingleton()
		{
			REL::Relocation<CombatBehaviorTreeBlock*> singleton{ REL::ID(518807) };  
			return singleton.get();
		}

		void Initialize() override;
	};

	class CombatBehaviorTreeCloseMovement : public CombatBehaviorTree
	{
	public:
		static CombatBehaviorTreeCloseMovement* GetSingleton()
		{
			REL::Relocation<CombatBehaviorTreeCloseMovement*> singleton{ REL::ID(518824) };  
			return singleton.get();
		}

		void Initialize() override;
	};

}
