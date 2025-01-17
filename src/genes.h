#pragma once
#include <sqlite3.h>

#include <map>

#include "db/db-connection.h"
#include "stats.h"

class GeneCategory {
   public:
	GeneCategory() = delete;
	GeneCategory(GeneCategory&&) = default;

	GeneCategory& operator=(const GeneCategory&) = delete;
	GeneCategory& operator=(GeneCategory&&) = delete;

	const int id;

	// Stats for recessive and dominant genes
	// Only one are used at the time by one pony
	Stats recessive_stats;
	Stats dominant_stats;

	// Because many ponies can use the same categories, it's better to store them
	// in some global container.
	static std::map<int, GeneCategory> categories;

   private:
	GeneCategory(int id) : id{id} {}

	friend GeneCategory load_gene_category_from_statement(sqlite3_stmt* stmt);
	friend GeneCategory& create_gene_category(DbConnection db);
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

	// a - recessive part
	// A - dominant part
	// When at least one part is dominant, then the whole gene is dominant
	enum Type { aa, aA, Aa, AA } type;

	// Get recessive or dominant stats based on the type
	Stats get_stats_modifier() const;

   private:
	Gene(int id, const GeneCategory& category) : id{id}, category{category} {}

	friend Gene load_gene_from_statement(sqlite3_stmt* stmt);
};
