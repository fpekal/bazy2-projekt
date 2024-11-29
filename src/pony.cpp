#include "pony.h"

Stats Pony::default_stats {};

Stats Pony::get_effective_stats() const {
	auto now = default_stats;

	for (auto& gene : genes) {
		now += gene.get_stats_modifier();
	}

	return now + learned_stats;
}
