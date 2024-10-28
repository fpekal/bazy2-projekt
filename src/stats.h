#pragma once

class Stats {
public:
	int max_health = 0;

	int min_damage = 0;
	int max_damage = 0;

	int attack_speed = 0;

	int armor = 0;

	int health_regeneration = 0;

	Stats operator+(const Stats& other) const;
	Stats& operator+=(const Stats& other);
};
