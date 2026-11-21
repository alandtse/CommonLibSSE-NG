#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/V/Variable.h"

namespace RE
{
	namespace BSScript
	{
		class IFunction;
		class ObjectTypeInfo;
		class Stack;

		class StackFrame
		{
		public:
			// Must be placed as part of a_stack's pages, never allocated directly
			explicit StackFrame(Stack* a_stack, std::uint32_t a_frameSize);

			~StackFrame();

			StackFrame(const StackFrame&) = delete;
			StackFrame(StackFrame&&) = delete;
			StackFrame& operator=(const StackFrame&) = delete;
			StackFrame& operator=(StackFrame&&) = delete;

			[[nodiscard]] std::uint32_t GetPageForFrame() const;
			[[nodiscard]] Variable&     GetStackFrameVariable(std::uint32_t a_index, std::uint32_t a_pageHint) const;

			bool InitFrame(BSTSmartPointer<IFunction>& a_function, const BSTSmartPointer<ObjectTypeInfo>& a_type, const Variable& a_self, const BSScrapArray<Variable>& a_args);

			// members
			Stack*                          parent;              // 00
			StackFrame*                     previousFrame;       // 08
			BSTSmartPointer<IFunction>      owningFunction{};    // 10
			BSTSmartPointer<ObjectTypeInfo> owningObjectType{};  // 18
			std::uint32_t                   instructionPointer;  // 20
			std::uint32_t                   pad24;               // 24
			Variable                        self{};              // 28
			std::uint32_t                   size;                // 38
			bool                            instructionsValid;   // 3C
			std::uint8_t                    pad3D;               // 3D
			std::uint16_t                   pad3E;               // 3E

			//Variable args[4];	40 - minimum space for 4 args is allocated
		};
		static_assert(sizeof(StackFrame) == 0x40);  // frames can be larger
	}
}
