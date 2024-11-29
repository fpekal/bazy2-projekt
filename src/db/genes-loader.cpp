#include "genes-loader.h"

#include <map>
#include <stdexcept>
#include <vector>

#include <sqlite3.h>

#include "../genes.h"

GeneCategory load_gene_category_from_statement(sqlite3_stmt* stmt) {
	GeneCategory out { sqlite3_column_int(stmt, 0) };
	out.recessive_stats.max_health = sqlite3_column_int(stmt, 1);
	out.recessive_stats.min_damage = sqlite3_column_int(stmt, 2);
	out.recessive_stats.max_damage = sqlite3_column_int(stmt, 3);
	out.recessive_stats.attack_speed = sqlite3_column_int(stmt, 4);
	out.recessive_stats.armor = sqlite3_column_int(stmt, 5);
	out.recessive_stats.health_regeneration = sqlite3_column_int(stmt, 6);
	out.dominant_stats.max_health = sqlite3_column_int(stmt, 7);
	out.dominant_stats.min_damage = sqlite3_column_int(stmt, 8);
	out.dominant_stats.max_damage = sqlite3_column_int(stmt, 9);
	out.dominant_stats.attack_speed = sqlite3_column_int(stmt, 10);
	out.dominant_stats.armor = sqlite3_column_int(stmt, 11);
	out.dominant_stats.health_regeneration = sqlite3_column_int(stmt, 12);
	return out;
}

std::map<int, GeneCategory> load_all_genes_categories(DbConnection db) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "SELECT * FROM gene_categories;";

	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	std::map<int, GeneCategory> out;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		auto gc = load_gene_category_from_statement(stmt);
		out.insert({gc.id, std::move(gc)});
	}

	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	return out;
}

Gene load_gene_from_statement(sqlite3_stmt* stmt) {
	GeneCategory& gc = GeneCategory::categories.at(sqlite3_column_int(stmt, 1));

	Gene out { sqlite3_column_int(stmt, 0), gc};
	out.type = static_cast<Gene::Type>(sqlite3_column_int(stmt, 2));
	return out;
}

Gene load_gene(DbConnection db, int id) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "SELECT * FROM genes WHERE id = ?;";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));
	res = sqlite3_bind_int(stmt, 1, id);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_step(stmt);
	if (res != SQLITE_ROW)
		throw std::runtime_error(sqlite3_errmsg(*db));

	Gene ret = load_gene_from_statement(stmt);
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	return ret;
}

std::vector<Gene> load_genes_for_pony(DbConnection db, const Pony& pony) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "SELECT gene_id FROM ponies_genes WHERE pony_id = ?;";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));
	res = sqlite3_bind_int(stmt, 1, pony.id);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	std::vector<Gene> out;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		out.push_back(load_gene(db, sqlite3_column_int(stmt, 0)));
	}

	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	return out;
}
