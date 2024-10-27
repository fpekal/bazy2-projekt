#include "stats.h"

Stats Stats::operator+(const Stats& other) const {
	Stats out;
	out.maxHealth = maxHealth + other.maxHealth;
	out.minDamage = minDamage + other.minDamage;
	out.maxDamage = maxDamage + other.maxDamage;
	out.attackSpeed = attackSpeed + other.attackSpeed;
	out.defense = defense + other.defense;
	out.healthRegen = healthRegen + other.healthRegen;
	return out;
}

Stats& Stats::operator+=(const Stats& other) {
	maxHealth += other.maxHealth;
	minDamage += other.minDamage;
	maxDamage += other.maxDamage;
	attackSpeed += other.attackSpeed;
	defense += other.defense;
	healthRegen += other.healthRegen;
	return *this;
}
