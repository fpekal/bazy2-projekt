#pragma once

class Stats {
public:
	int maxHealth = 0;

	int minDamage = 0;
	int maxDamage = 0;

	int attackSpeed = 0;

	int armor = 0;

	int healthRegeneration = 0;

	Stats operator+(const Stats& other) const;
	Stats& operator+=(const Stats& other);
};
