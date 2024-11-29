#include "genes-saver.h"

#include <sqlite3.h>
#include <map>
#include <stdexcept>

#include "genes-loader.h"

void update_gene_category(DbConnection db, const GeneCategory& gc) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "UPDATE gene_categories SET "
		"recessive_max_health = ?,"
		"recessive_min_damage = ?,"
		"recessive_max_damage = ?,"
		"recessive_attack_speed = ?,"
		"recessive_armor = ?,"
		"recessive_health_regeneration = ?,"
		"dominant_max_health = ?,"
		"dominant_min_damage = ?,"
		"dominant_max_damage = ?,"
		"dominant_attack_speed = ?,"
		"dominant_armor = ?,"
		"dominant_health_regeneration = ? "
		"WHERE id = ?;";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 1, gc.recessive_stats.max_health);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 2, gc.recessive_stats.min_damage);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 3, gc.recessive_stats.max_damage);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 4, gc.recessive_stats.attack_speed);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 5, gc.recessive_stats.armor);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 6, gc.recessive_stats.health_regeneration);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 7, gc.dominant_stats.max_health);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 8, gc.dominant_stats.min_damage);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 9, gc.dominant_stats.max_damage);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 10, gc.dominant_stats.attack_speed);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 11, gc.dominant_stats.armor);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 12, gc.dominant_stats.health_regeneration);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 13, gc.id);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_step(stmt);
	if (res != SQLITE_DONE)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));
}

GeneCategory& create_gene_category(DbConnection db) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "INSERT INTO gene_categories ("
		"recessive_max_health,"
		"recessive_min_damage,"
		"recessive_max_damage,"
		"recessive_attack_speed,"
		"recessive_armor,"
		"recessive_health_regeneration,"
		"dominant_max_health,"
		"dominant_min_damage,"
		"dominant_max_damage,"
		"dominant_attack_speed,"
		"dominant_armor,"
		"dominant_health_regeneration"
		") VALUES (0,0,0,0,0,0,0,0,0,0,0,0);";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_step(stmt);
	if (res != SQLITE_DONE)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_last_insert_rowid(*db);
	if (res == 0)
		throw std::runtime_error("Failed to create gene category");

	GeneCategory::categories.insert({res, GeneCategory(res)});

	return GeneCategory::categories.at(res);
}

void delete_gene_category(DbConnection db, int id) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "DELETE FROM gene_categories WHERE id = ?;";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));
	res = sqlite3_bind_int(stmt, 1, id);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));
	res = sqlite3_step(stmt);
	if (res != SQLITE_DONE)
		throw std::runtime_error(sqlite3_errmsg(*db));
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	GeneCategory::categories.erase(id);
}
