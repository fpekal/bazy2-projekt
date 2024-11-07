#include <iostream>
#include <fstream>
#include <string>

#include <sqlite3.h>

#include "db/db-connection.h"
#include "db/pony-loader.h"
#include "db/pony-saver.h"
#include "tui/draw-pony.h"

std::string load_scheme() {
	std::ifstream ifs("sql/make_scheme.sql");
	std::string sql((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	return sql;
}

int main() {
	DbConnection db = open_db("file:pony.db");

	sqlite3_exec(*db, load_scheme().c_str(), nullptr, nullptr, nullptr);
	
	{
		Pony p = create_pony(db, "Pinkie Pie");

		p.health = 12;

		p.learned_stats.max_health = 10;
		p.learned_stats.min_damage = 1;
		p.learned_stats.max_damage = 1;
		p.learned_stats.attack_speed = 1;
		p.learned_stats.armor = 1;
		p.learned_stats.health_regeneration = 1;

		update_pony(db, p);

		draw_pony(p);
	}

	{
		Pony p = create_pony(db, "Fluttershy");

		p.health = 34;

		p.learned_stats.max_health = 40;
		p.learned_stats.min_damage = 2;
		p.learned_stats.max_damage = 1;
		p.learned_stats.attack_speed = 3;
		p.learned_stats.armor = 7;
		p.learned_stats.health_regeneration = 0;

		update_pony(db, p);

		draw_pony(p);
	}
}

