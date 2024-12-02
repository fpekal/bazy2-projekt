#pragma once

class Stats {
public:
	int max_health = 0;

	// Damage is chosen randomly between min_damage and max_damage
	int min_damage = 0;
	int max_damage = 0;

	// How many rounds pony waits for its next attack
	// So, less attack_speed results in faster attacks (subject to change)
	int attack_speed = 0;

	// Explained in depth in documentation
	int armor = 0;

	// Again, explained in documentation
	int health_regeneration = 0;

	Stats operator+(const Stats& other) const;
	Stats& operator+=(const Stats& other);
};
