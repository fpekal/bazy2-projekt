#include "pony-loader.h"

#include <stdexcept>
#include <string>
#include <vector>

#include <sqlite3.h>

#include "genes-loader.h"

Pony load_pony_from_statement(sqlite3_stmt* stmt) {
	Pony out { sqlite3_column_int(stmt, 0) };
	out.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
	out.health = sqlite3_column_int(stmt, 2);
	out.learned_stats.max_health = sqlite3_column_int(stmt, 3);
	out.learned_stats.min_damage = sqlite3_column_int(stmt, 4);
	out.learned_stats.max_damage = sqlite3_column_int(stmt, 5);
	out.learned_stats.attack_speed = sqlite3_column_int(stmt, 6);
	out.learned_stats.armor = sqlite3_column_int(stmt, 7);
	out.learned_stats.health_regeneration = sqlite3_column_int(stmt, 8);

	return out;
}

Pony load_pony(DbConnection db, int id) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "SELECT * FROM ponies WHERE id = ?;";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));
	res = sqlite3_bind_int(stmt, 1, id);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_step(stmt);
	if (res != SQLITE_ROW)
		throw std::runtime_error(sqlite3_errmsg(*db));

	Pony ret = load_pony_from_statement(stmt);
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	ret.genes = load_genes_for_pony(db, ret);

	return ret;
}

Pony load_pony(DbConnection db, const std::string& name) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "SELECT * FROM ponies WHERE name = ?;";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));
	res = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_step(stmt);
	if (res != SQLITE_ROW)
		throw std::runtime_error(sqlite3_errmsg(*db));

	Pony ret = load_pony_from_statement(stmt);
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	ret.genes = load_genes_for_pony(db, ret);

	return ret;
}

std::vector<Pony> load_all_ponies(DbConnection db) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "SELECT * FROM ponies;";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	std::vector<Pony> out;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		out.push_back(load_pony_from_statement(stmt));
	}
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	return out;
}
