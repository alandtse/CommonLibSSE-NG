#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiAVObject;
	class BGSHeadPart;
	class BSFaceGenModel;
	class BSFaceGenNiNode;
	class TESNPC;

	struct BSFaceGenModelMap
	{
	public:
		class Entry : public NiRefObject
		{
		public:
			// members
			NiPointer<BSFaceGenModel> model;  // 10
			std::uint64_t             time;   // 18
		};
		static_assert(sizeof(Entry) == 0x20);

		// members
		BSTHashMap<BSFixedString, NiPointer<Entry>> map;             // 00
		BSReadWriteLock                             lock;            // 30
		bool                                        hasFaceGenData;  // 38
	};
	static_assert(sizeof(BSFaceGenModelMap) == 0x40);

	class BSFaceGenManager : public BSTSingletonSDM<BSFaceGenManager>
	{
	public:
		[[nodiscard]] static BSFaceGenManager* GetSingleton()
		{
			static REL::Relocation<BSFaceGenManager**> singleton{ RELOCATION_ID(514182, 400331) };
			return *singleton;
		}

		void PrepareHeadPartForShaders(BSFaceGenNiNode* a_node, BGSHeadPart* a_headPart, TESNPC* a_npc)
		{
			using func_t = decltype(&BSFaceGenManager::PrepareHeadPartForShaders);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26259, 26838) };
			return func(this, a_node, a_headPart, a_npc);
		}

		void GetModel(const char* a_modelPath, const char* a_triPath, NiPointer<BSFaceGenModel>& a_out, bool a_loadIfMissing, bool a_unk)
		{
			using func_t = void(BSFaceGenManager*, const char*, const char*, NiPointer<BSFaceGenModel>&, bool, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26246, 26825) };
			func(this, a_modelPath, a_triPath, a_out, a_loadIfMissing, a_unk);
		}

		void PurgeUnusedModels()
		{
			using func_t = void(BSFaceGenManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26247, 26826) };
			func(this);
		}

		void ResetToBaseMorph(NiAVObject* a_geometry)
		{
			using func_t = void(BSFaceGenManager*, NiAVObject*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26250, 26829) };
			func(this, a_geometry);
		}

		// members
		std::uint32_t     numActorsToMorph;  // 04
		bool              emotions;          // 08
		std::uint8_t      pad09[7];          // 09
		std::uint64_t     unk10;             // 10
		BSFaceGenModelMap modelMap;          // 18
		std::uint8_t      isReset;           // 58
		std::uint8_t      pad59[3];          // 59
		std::uint32_t     unk5C;             // 5C
		std::uint8_t      unk60;             // 60
		std::uint8_t      pad61[7];          // 61
	};
	static_assert(sizeof(BSFaceGenManager) == 0x68);
};
