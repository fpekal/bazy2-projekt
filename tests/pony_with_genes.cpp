#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <stdlib.h>

#include "pony.h"
#include "genes.h"
#include "db/db-connection.h"
#include "db/scheme.h"
#include "db/pony-loader.h"
#include "db/pony-saver.h"
#include "db/genes-loader.h"
#include "db/genes-saver.h"

BOOST_AUTO_TEST_CASE(pony_with_genes) {
	std::ignore = system("rm pony_test.db 2> /dev/null");
	
	DbConnection db = open_db("file:pony_test.db");
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

	{
		Pony pony = load_pony(db, "Pinkie Pie");
		
		auto stats = pony.get_effective_stats();

		BOOST_CHECK(stats.max_health == 110);
	}

	{
		g.type = Gene::Type::aA;
		update_gene(db, g);

		Pony pony = load_pony(db, 1);
		
		auto stats = pony.get_effective_stats();
		
		BOOST_CHECK(stats.max_health == 210);
	}
	
	std::ignore = system("rm pony_test.db 2> /dev/null");
}
