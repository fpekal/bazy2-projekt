#include "stats.h"

Stats Stats::operator+(const Stats& other) const {
	Stats out;
	out.maxHealth = maxHealth + other.maxHealth;
	out.minDamage = minDamage + other.minDamage;
	out.maxDamage = maxDamage + other.maxDamage;
	out.attackSpeed = attackSpeed + other.attackSpeed;
	out.armor = armor + other.armor;
	out.healthRegeneration = healthRegeneration + other.healthRegeneration;
	return out;
}

Stats& Stats::operator+=(const Stats& other) {
	maxHealth += other.maxHealth;
	minDamage += other.minDamage;
	maxDamage += other.maxDamage;
	attackSpeed += other.attackSpeed;
	armor += other.armor;
	healthRegeneration += other.healthRegeneration;
	return *this;
}
