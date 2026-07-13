#include "RE/B/BSTreeNode.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void BSTreeNode::OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex)
	{
		REL::RelocateVirtual<decltype(&BSTreeNode::OnVisible)>(0x34, 0x35, this, a_process, a_alphaGroupIndex);
	}
#endif
}
