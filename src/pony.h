#pragma once
#include <string>

#include "stats.h"

class Pony {
public:
	int id;
	std::string name;
	int health;
	Stats learned_stats;

	static Stats default_stats;

	Stats get_effective_stats() const;
};
