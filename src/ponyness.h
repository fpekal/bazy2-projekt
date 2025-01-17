#pragma once

#include "pony.h"
#include "stats.h"

// Jak sama nazwa wskazuje, wylicza kucykowość
long long calculate_ponyness(const Pony& pony) {
	auto stats = pony.get_effective_stats();

	return stats.max_health + stats.min_damage + stats.max_damage - stats.attack_speed + stats.armor + stats.health_regeneration;
}
