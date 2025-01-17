#pragma once
#include <sqlite3.h>

#include <string>
#include <vector>

#include "genes.h"
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

	std::vector<Gene> genes;

	// Starting point for every pony
	// Rest of stats are added/subtracted from this (or other operations are used)
	static Stats default_stats;

	// Calculates final stats that will be used in battles.
	// Mutations(Default + Learned + Genes)
	// Where "Mutations" are arbitrary functions
	Stats get_effective_stats() const;

   private:
	// Private because there should not be any pony that aren't in the database
	Pony(int id) : id{id} {};

	friend Pony load_pony_from_statement(sqlite3_stmt* stmt);
};
