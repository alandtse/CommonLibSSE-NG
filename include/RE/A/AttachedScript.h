#pragma once

#include "RE/B/BSTPointerAndFlags.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/O/Object.h"

namespace RE
{
	namespace BSScript
	{
		namespace Internal
		{
			class AttachedScript : public BSTPointerAndFlags<BSTSmartPointer<Object>, 1>
			{
			public:
				AttachedScript(BSTSmartPointer<Object> a_object, bool a_diskLoaded) noexcept :
					BSTPointerAndFlags<BSTSmartPointer<Object>, 1>()
				{
					_storage.ptr = a_object;
					_storage.address |= static_cast<std::uintptr_t>(a_diskLoaded);
				}

				bool DiskLoaded() const
				{
					return _storage.address & FLAG_MASK;
				}
			};
			static_assert(sizeof(AttachedScript) == 0x8);
		}
	}
}
