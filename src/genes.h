#pragma once
#include <map>

#include <sqlite3.h>

#include "stats.h"

class GeneCategory {
public:
	GeneCategory() = delete;
	GeneCategory(const GeneCategory&) = default;
	GeneCategory(GeneCategory&&) = default;

	GeneCategory& operator=(const GeneCategory&) = delete;
	GeneCategory& operator=(GeneCategory&&) = delete;

	const int id;

	Stats recessive_stats;
	Stats dominant_stats;

	static std::map<int, GeneCategory> categories;

private:
	GeneCategory(int id) : id{ id } {}

	friend GeneCategory load_gene_category_from_statement(sqlite3_stmt* stmt);
};

class Gene {
public:
	Gene() = delete;
	Gene(const Gene&) = default;
	Gene(Gene&&) = default;

	Gene& operator=(const Gene&) = delete;
	Gene& operator=(Gene&&) = delete;

	const int id;
	const GeneCategory& category;

	enum Type {
		aa,aA,Aa,AA
	} type;


	Stats get_stats_modifier() const;

private:
	Gene(int id, const GeneCategory& category) : id{ id }, category{ category } {}
};
