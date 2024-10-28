#include "pony-loader.h"

#include <stdexcept>

#include <sqlite3.h>

static Pony load_pony_from_statement(sqlite3_stmt* stmt) {
	Pony out;
	out.id = sqlite3_column_int(stmt, 0);
	out.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
	out.health = sqlite3_column_int(stmt, 2);
	out.learned_stats.maxHealth = sqlite3_column_int(stmt, 3);
	out.learned_stats.minDamage = sqlite3_column_int(stmt, 4);
	out.learned_stats.maxDamage = sqlite3_column_int(stmt, 5);
	out.learned_stats.attackSpeed = sqlite3_column_int(stmt, 6);
	out.learned_stats.armor = sqlite3_column_int(stmt, 7);
	out.learned_stats.healthRegeneration = sqlite3_column_int(stmt, 8);
	return out;
}

Pony load_pony(DbConnection db, int id) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "SELECT * FROM ponies WHERE id = ?;";
	sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	sqlite3_bind_int(stmt, 1, id);

	int res = sqlite3_step(stmt);
	if (res != SQLITE_ROW)
		throw std::runtime_error(sqlite3_errmsg(*db));

	Pony ret = load_pony_from_statement(stmt);
	sqlite3_finalize(stmt);

	return ret;
}

Pony load_pony(DbConnection db, const std::string& name) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "SELECT * FROM ponies WHERE name = ?;";
	sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

	int res = sqlite3_step(stmt);
	if (res != SQLITE_ROW)
		throw std::runtime_error(sqlite3_errmsg(*db));

	Pony ret = load_pony_from_statement(stmt);
	sqlite3_finalize(stmt);

	return ret;
}

std::vector<Pony> load_all_ponies(DbConnection db) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "SELECT * FROM ponies;";
	sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);

	std::vector<Pony> out;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		out.push_back(load_pony_from_statement(stmt));
	}
	sqlite3_finalize(stmt);

	return out;
}
