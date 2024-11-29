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
	
	auto g = create_gene(db, GeneCategory::categories.at(2));

	std::cout << g.id << '\n';
	g.type = Gene::Type::aa;
	std::cout << g.get_stats_modifier().max_health << '\n';
	
	return 0;
}

