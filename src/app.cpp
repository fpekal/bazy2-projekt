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

	GeneCategory& gc = create_gene_category(db);

	gc.recessive_stats.max_health = 20;
	gc.dominant_stats.max_health = 0;

	gc.recessive_stats.health_regeneration = 0;
	gc.dominant_stats.health_regeneration = 5;

	update_gene_category(db, gc);

	try {
		Pony p = create_pony(db, "Twilight Sparkle");

		Gene g = create_gene(db, gc, p);
		g.type = Gene::Type::Aa;
		update_gene(db, g);
	}
	catch (const std::runtime_error& e) {
	}

	Pony p = load_pony(db, "Twilight Sparkle");
	draw_pony(p);
}

