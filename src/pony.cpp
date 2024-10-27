#include "pony.h"

#include <array>

Stats Pony::default_stats {};

Stats Pony::get_effective_stats() const {
	// Tablica wskaźników do wszystkich memberów klasy Stats.
	// Można to tak zapisać, bo wszystkie membery są tego samego typu.
	// Jeżeli w przyszłości jakiś typ zostanie zmieniony to lepiej to napisać
	// jakąś zwykłą sumą memberów.
	constexpr static std::array<int Stats::*, 6> members {
		&Stats::maxHealth,
		&Stats::minDamage,
		&Stats::maxDamage,
		&Stats::attackSpeed,
		&Stats::defense,
		&Stats::healthRegen
	};

	Stats out;

	for (auto member : members) {
		out.*member = learned_stats.*member + default_stats.*member;
	}

	return out;
}
