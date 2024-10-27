#include "pony.h"

#include <array>

Stats Pony::default_stats {};

Stats Pony::get_effective_stats() const {
	return default_stats + learned_stats;
}
