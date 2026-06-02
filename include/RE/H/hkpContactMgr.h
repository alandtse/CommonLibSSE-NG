#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkpContactMgr : public hkReferencedObject  // hkReferencedObject base = 0x10
	{
	public:
		enum class Type
		{
			kInvalid = 0,
			kSimpleConstraint,
			kReportContact,
			kMax
		};

		~hkpContactMgr() override;  // 00

		// members
		std::int32_t  type;   // 10
		std::uint32_t pad14;  // 14
	};
	static_assert(sizeof(hkpContactMgr) == 0x18);
}
