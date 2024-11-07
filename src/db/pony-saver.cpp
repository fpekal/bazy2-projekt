#include "pony-saver.h"

#include <stdexcept>
#include <string>

#include <sqlite3.h>

#include "pony-loader.h"

void update_pony(DbConnection db, const Pony& pony) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "UPDATE ponies SET name = ?, health = ?, max_health = ?, min_damage = ?, max_damage = ?, attack_speed = ?, armor = ?, health_regeneration = ? WHERE id = ?;";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_text(stmt, 1, pony.name.c_str(), -1, SQLITE_STATIC);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 2, pony.health);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 3, pony.learned_stats.max_health);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 4, pony.learned_stats.min_damage);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 5, pony.learned_stats.max_damage);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 6, pony.learned_stats.attack_speed);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 7, pony.learned_stats.armor);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 8, pony.learned_stats.health_regeneration);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_int(stmt, 9, pony.id);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_step(stmt);
	if (res != SQLITE_DONE)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));
}


Pony create_pony(DbConnection db, const std::string& name) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "INSERT INTO ponies (name, health, max_health, min_damage, max_damage, attack_speed, armor, health_regeneration) VALUES (?, 10, 0, 0, 0, 0, 0, 0);";
	int res = sqlite3_prepare_v2(*db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_step(stmt);
	if (res != SQLITE_DONE)
		throw std::runtime_error(sqlite3_errmsg(*db));

	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK)
		throw std::runtime_error(sqlite3_errmsg(*db));

	return load_pony(db, name);
}


void delete_pony(DbConnection db, int id) {
	sqlite3_stmt* stmt = nullptr;
	const char* sql = "DELETE FROM ponies WHERE id = ?;";
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
}
