#include "stats.h"

Stats Stats::operator+(const Stats& other) const {
	Stats out;
	out.max_health = max_health + other.max_health;
	out.min_damage = min_damage + other.min_damage;
	out.max_damage = max_damage + other.max_damage;
	out.attack_speed = attack_speed + other.attack_speed;
	out.armor = armor + other.armor;
	out.health_regeneration = health_regeneration + other.health_regeneration;
	return out;
}

Stats& Stats::operator+=(const Stats& other) {
	max_health += other.max_health;
	min_damage += other.min_damage;
	max_damage += other.max_damage;
	attack_speed += other.attack_speed;
	armor += other.armor;
	health_regeneration += other.health_regeneration;
	return *this;
}
