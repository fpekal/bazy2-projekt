#include "fight.h"

void Fight::make_turn(Pony& attacking, Pony& defending) {
	attacking.health += attacking.get_effective_stats().health_regeneration;
	attacking.health = std::min(attacking.health, attacking.get_effective_stats().max_health);

	// Get random attack damage from min to max
	int damage = rand() % (attacking.get_effective_stats().max_damage -
						   attacking.get_effective_stats().min_damage + 1) +
				 attacking.get_effective_stats().min_damage;

	int change_health = 0;
	// Check if defending pony should be damaged
	if (defending.get_effective_stats().armor <= damage) {
		change_health = damage;
	}

	// Apply damage to defending pony
	defending.health -= change_health;
}

void Fight::make_turn() {
	if (waiting_left <= 0) {
		make_turn(left_pony, right_pony);
		waiting_left = left_pony.get_effective_stats().attack_speed + 1;
	}
	if (waiting_right <= 0) {
		make_turn(right_pony, left_pony);
		waiting_right = right_pony.get_effective_stats().attack_speed + 1;
	}
	--waiting_left;
	--waiting_right;
}

Fight::Direction Fight::fight() {
	int i = 0;

	while (true) {
		make_turn();

		if (left_pony.health <= 0 && right_pony.health <= 0) {
			left_pony.health = 0;
			right_pony.health = 0;
			return Direction::DRAW;
		}
		if (left_pony.health <= 0) {
			left_pony.health = 0;
			return Direction::RIGHT;
		}
		if (right_pony.health <= 0) {
			right_pony.health = 0;
			return Direction::LEFT;
		}

		++i;
		if (i > 1000) {
			return Direction::DRAW;
		}
	}
}
