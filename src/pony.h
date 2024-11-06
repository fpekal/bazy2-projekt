#pragma once
#include <string>

#include <sqlite3.h>

#include "stats.h"

class Pony {
public:
	// Getting pony object is only allowed from load_pony() or from create_pony().
	Pony() = delete;
	Pony(const Pony&) = default;
	Pony(Pony&&) = default;

	Pony& operator=(const Pony&) = delete;
	Pony& operator=(Pony&&) = delete;

	const int id;
	std::string name;
	int health;
	Stats learned_stats;

	static Stats default_stats;

	Stats get_effective_stats() const;

private:
	Pony(int id) : id{ id } {};

	friend Pony load_pony_from_statement(sqlite3_stmt* stmt);
};
