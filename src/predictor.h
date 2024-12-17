#pragma once
#include <limits>

#include "pony.h"
#include "stats.h"

template<typename Cont>
std::pair<Pony, Pony> predict(const Cont& ponies, const Stats& stats) {
	int best_index1 = 0;
	int best_index2 = 0;
	int best_sum = std::numeric_limits<int>::max();

	for (unsigned int i = 0; i < ponies.size() - 1; i++) {
		for (unsigned int j = i + 1; j < ponies.size(); j++) {
			auto stats1 = ponies[i].get_effective_stats();
			auto stats2 = ponies[j].get_effective_stats();

			Stats merged = stats1 + stats2;
			merged.max_health /= 2;
			merged.min_damage /= 2;
			merged.max_damage /= 2;
			merged.attack_speed /= 2;
			merged.armor /= 2;
			merged.health_regeneration /= 2;

			int sum = 0;
			sum += std::abs(merged.max_health - stats.max_health);
			sum += std::abs(merged.min_damage - stats.min_damage);
			sum += std::abs(merged.max_damage - stats.max_damage);
			sum += std::abs(merged.attack_speed - stats.attack_speed);
			sum += std::abs(merged.armor - stats.armor);
			sum += std::abs(merged.health_regeneration - stats.health_regeneration);

			if (sum < best_sum) {
				best_sum = sum;
				best_index1 = i;
				best_index2 = j;
			}
		}
	}

	return std::make_pair(ponies[best_index1], ponies[best_index2]);
}
