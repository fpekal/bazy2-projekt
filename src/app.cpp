#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

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

	Pony pony = create_pony(db, "Pinkie Pie");
	pony.learned_stats.max_health = 10;
	update_pony(db, pony);
	
	auto& gc = create_gene_category(db);
	gc.recessive_stats.max_health = 100;
	gc.dominant_stats.max_health = 200;
	update_gene_category(db, gc);

	auto g = create_gene(db, gc, pony);
	g.type = Gene::Type::aa;
	update_gene(db, g);

	std::cout << pony.genes.size() << std::endl;
	
	{
		Pony pony = load_pony(db, "Pinkie Pie");
		
		auto stats = pony.get_effective_stats();

		assert(stats.max_health == 110);
	}

	{
		g.type = Gene::Type::aA;
		update_gene(db, g);

		Pony pony = load_pony(db, "Pinkie Pie");
		
		auto stats = pony.get_effective_stats();
		
		assert(stats.max_health == 210);
	}
}

