#include "genes.h"

#include "stats.h"

Stats Gene::get_stats_modifier() const {
	switch (type) {
	case aA: [[fallthrough]];
	case Aa: [[fallthrough]];
	case AA:
		return category.dominant_stats;

	case aa:
		return category.recessive_stats;

	default:
		return Stats();
	}
}
