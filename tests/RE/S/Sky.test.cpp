#include "catch2/catch_all.hpp"

#include "RE/S/Sky.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

static_assert(std::is_same_v<decltype(RE::TESWeather::Data::precipitationBeginFadeIn), std::uint8_t>);
static_assert(std::is_same_v<decltype(RE::TESWeather::Data::precipitationEndFadeOut), std::uint8_t>);
static_assert(offsetof(RE::TESWeather::Data, precipitationBeginFadeIn) == 0x6);
static_assert(offsetof(RE::TESWeather::Data, precipitationEndFadeOut) == 0x7);

namespace
{
	template <class T>
	struct EngineStorage
	{
		alignas(T) std::array<std::byte, sizeof(T)> bytes{};
		T* get() { return reinterpret_cast<T*>(bytes.data()); }
	};
}

TEST_CASE("Sky/Precipitation covers every stored byte", "[unit][weather]")
{
	EngineStorage<RE::Sky>        skyStorage;
	EngineStorage<RE::TESWeather> weatherStorage;
	auto*                         sky = skyStorage.get();
	auto*                         weather = weatherStorage.get();

	for (auto flag : { RE::TESWeather::WeatherDataFlag::kRainy, RE::TESWeather::WeatherDataFlag::kSnow }) {
		weather->data.flags = flag;
		for (unsigned value = 0; value <= 255; ++value) {
			weather->data.precipitationBeginFadeIn = static_cast<std::uint8_t>(value);
			weather->data.precipitationEndFadeOut = static_cast<std::uint8_t>(value);
			for (float progress : { 0.0F, 0.25F, 0.5F, 0.75F, 1.0F }) {
				CAPTURE(flag, value, progress);
				sky->currentWeatherPct = progress;
				sky->currentWeather = weather;
				sky->lastWeather = nullptr;
				const bool started = value * 999.0 < progress * 255000.0;
				CHECK(sky->IsRaining() == (started && flag == RE::TESWeather::WeatherDataFlag::kRainy));
				CHECK(sky->IsSnowing() == (started && flag == RE::TESWeather::WeatherDataFlag::kSnow));
				sky->currentWeather = nullptr;
				sky->lastWeather = weather;
				const bool remaining = value * 999.0 + 255.0 > progress * 255000.0;
				CHECK(sky->IsRaining() == (remaining && flag == RE::TESWeather::WeatherDataFlag::kRainy));
				CHECK(sky->IsSnowing() == (remaining && flag == RE::TESWeather::WeatherDataFlag::kSnow));
			}
		}
	}
}

TEST_CASE("Sky/Precipitation preserves native endpoint margins", "[unit][weather]")
{
	EngineStorage<RE::Sky>        skyStorage;
	EngineStorage<RE::TESWeather> weatherStorage;
	auto*                         sky = skyStorage.get();
	auto*                         weather = weatherStorage.get();
	weather->data.flags.set(RE::TESWeather::WeatherDataFlag::kRainy, RE::TESWeather::WeatherDataFlag::kSnow);
	auto check = [&](bool a_expected) {
		CHECK(sky->IsRaining() == a_expected);
		CHECK(sky->IsSnowing() == a_expected);
	};

	sky->currentWeather = weather;
	weather->data.precipitationBeginFadeIn = 0;
	sky->currentWeatherPct = 0.0F;
	check(false);
	sky->currentWeatherPct = 0.0005F;
	check(true);
	weather->data.precipitationBeginFadeIn = 255;
	sky->currentWeatherPct = 0.998F;
	check(false);
	sky->currentWeatherPct = 0.9995F;
	check(true);
	sky->currentWeatherPct = 1.0F;
	check(true);

	sky->currentWeather = nullptr;
	sky->lastWeather = weather;
	weather->data.precipitationEndFadeOut = 0;
	sky->currentWeatherPct = 0.0F;
	check(true);
	sky->currentWeatherPct = 0.0005F;
	check(true);
	sky->currentWeatherPct = 0.001F;
	check(false);
	weather->data.precipitationEndFadeOut = 255;
	sky->currentWeatherPct = 0.9995F;
	check(true);
	sky->currentWeatherPct = 1.0F;
	check(false);
}

TEST_CASE("Sky/Precipitation combines matching weather only", "[unit][weather]")
{
	EngineStorage<RE::Sky>        skyStorage;
	EngineStorage<RE::TESWeather> currentStorage;
	EngineStorage<RE::TESWeather> lastStorage;
	auto*                         sky = skyStorage.get();
	CHECK_FALSE(sky->IsRaining());
	CHECK_FALSE(sky->IsSnowing());
	sky->currentWeather = currentStorage.get();
	sky->lastWeather = lastStorage.get();
	currentStorage.get()->data.flags = RE::TESWeather::WeatherDataFlag::kSnow;
	currentStorage.get()->data.precipitationBeginFadeIn = 64;
	lastStorage.get()->data.flags = RE::TESWeather::WeatherDataFlag::kRainy;
	lastStorage.get()->data.precipitationEndFadeOut = 192;
	sky->currentWeatherPct = 0.25F;
	CHECK(sky->IsRaining());
	CHECK_FALSE(sky->IsSnowing());
	sky->currentWeatherPct = 0.5F;
	CHECK(sky->IsRaining());
	CHECK(sky->IsSnowing());
	sky->currentWeatherPct = 0.754F;
	CHECK_FALSE(sky->IsRaining());
	CHECK(sky->IsSnowing());
	currentStorage.get()->data.flags = RE::TESWeather::WeatherDataFlag::kPleasant;
	lastStorage.get()->data.flags = RE::TESWeather::WeatherDataFlag::kCloudy;
	CHECK_FALSE(sky->IsRaining());
	CHECK_FALSE(sky->IsSnowing());
}
