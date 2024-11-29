#include <iostream>
#include <fstream>
#include <string>

#include <sqlite3.h>

#include "db/db-connection.h"
#include "db/pony-loader.h"
#include "db/pony-saver.h"
#include "db/scheme.h"
#include "tui/draw-pony.h"
#include "db/genes-loader.h"
#include "db/genes-saver.h"

int main() {
	DbConnection db = open_db("file:pony.db");

	run_scheme(db);
	GeneCategory::categories = load_all_genes_categories(db);
	
	auto gc = create_gene_category(db);
	gc.recessive_stats.max_health = 100;
	gc.recessive_stats.min_damage = 100;
	gc.recessive_stats.max_damage = 100;
	gc.recessive_stats.attack_speed = 100;
	gc.recessive_stats.armor = 100;
	gc.recessive_stats.health_regeneration = 100;
	gc.dominant_stats.max_health = 100;
	gc.dominant_stats.min_damage = 100;
	gc.dominant_stats.max_damage = 100;
	gc.dominant_stats.attack_speed = 100;
	gc.dominant_stats.armor = 100;
	gc.dominant_stats.health_regeneration = 100;

	update_gene_category(db, gc);

	delete_gene_category(db, 1);

	std::cout << GeneCategory::categories.at(1).dominant_stats.max_health;
	
	return 0;
}

