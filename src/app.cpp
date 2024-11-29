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
	
	auto& gc = create_gene_category(db);
	gc.recessive_stats.max_health = 10;
	gc.dominant_stats.max_health = 50;
	update_gene_category(db, gc);

	auto g = create_gene(db, gc);
	g.type = Gene::Type::aA;
	update_gene(db, g);

	std::cout << g.get_stats_modifier().max_health << std::endl;
	
	return 0;
}

