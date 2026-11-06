#include "catch2/catch_all.hpp"

#include "RE/R/RaceSexMenu.h"

#include <cstddef>

namespace
{
	template <class T>
	concept HasEmbeddedCamera = requires(T& a_menu) { a_menu.camera; };
}

TEST_CASE("RaceSexMenu/RuntimeDataLayouts", "[unit][race-sex-menu]")
{
	using FlatData = RE::RaceSexMenu::RUNTIME_DATA;
	using VRData = RE::RaceSexMenu::VR_RUNTIME_DATA;

	CHECK(sizeof(FlatData) == 0x168);
	CHECK(offsetof(FlatData, headParts) == 0x0);
	CHECK(offsetof(FlatData, camera) == 0xA8);
	CHECK(offsetof(FlatData, sliderData) == 0x100);
	CHECK(offsetof(FlatData, raceIndex) == 0x148);
	CHECK(offsetof(FlatData, sex) == 0x158);
	CHECK(offsetof(FlatData, unk1A4) == 0x164);

	CHECK(sizeof(VRData) == 0x110);
	CHECK(offsetof(VRData, headParts) == 0x0);
	CHECK(offsetof(VRData, sliderData) == 0xA8);
	CHECK(offsetof(VRData, raceIndex) == 0xF0);
	CHECK(offsetof(VRData, sex) == 0x100);
	CHECK(offsetof(VRData, unk1A4) == 0x10C);
	CHECK_FALSE(HasEmbeddedCamera<VRData>);
}

#ifndef SKYRIM_CROSS_VR
TEST_CASE("RaceSexMenu/DirectMemberLayout", "[unit][race-sex-menu]")
{
	using Menu = RE::RaceSexMenu;
#	ifdef EXCLUSIVE_SKYRIM_VR
	CHECK(sizeof(Menu) == 0x160);
	CHECK(offsetof(Menu, headParts) == 0x50);
	CHECK(offsetof(Menu, sliderData) == 0xF8);
	CHECK(offsetof(Menu, unk170) == 0x128);
	CHECK(offsetof(Menu, raceIndex) == 0x140);
	CHECK(offsetof(Menu, sex) == 0x150);
	CHECK(offsetof(Menu, unk1A4) == 0x15C);
	CHECK_FALSE(HasEmbeddedCamera<Menu>);
#	else
	CHECK(sizeof(Menu) == 0x1A8);
	CHECK(offsetof(Menu, headParts) == 0x40);
	CHECK(offsetof(Menu, camera) == 0xE8);
	CHECK(offsetof(Menu, sliderData) == 0x140);
	CHECK(offsetof(Menu, unk170) == 0x170);
	CHECK(offsetof(Menu, raceIndex) == 0x188);
	CHECK(offsetof(Menu, sex) == 0x198);
	CHECK(offsetof(Menu, unk1A4) == 0x1A4);
#	endif
}
#endif
