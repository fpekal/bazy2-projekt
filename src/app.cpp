#include <iostream>
#include <fstream>
#include <string>

#include <sqlite3.h>

#include "db/db-connection.h"
#include "db/pony-loader.h"

std::string load_scheme() {
	std::ifstream ifs("sql/make_scheme.sql");
	std::string sql((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	return sql;
}

int main() {
	DbConnection db = open_db("file:pony.db");

	sqlite3_exec(*db, load_scheme().c_str(), nullptr, nullptr, nullptr);
	sqlite3_exec(*db, "INSERT INTO ponies (name, health, max_health, min_damage, max_damage, attack_speed, armor, health_regeneration) VALUES ('Pony2', 2, 1, 3, 7, 4, 2, 0);", nullptr, nullptr, nullptr);

	Pony p = load_pony(db, 1);
	std::cout << p.get_effective_stats().max_health << std::endl;

	p = load_pony(db, "Pony2");
	std::cout << p.get_effective_stats().max_health << std::endl;

	auto all_ponies = load_all_ponies(db);
	for (auto& pony : all_ponies) {
		std::cout << pony.get_effective_stats().max_health << std::endl;
	}
}
