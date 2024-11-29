#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "db/db-connection.h"
#include "genes.h"
#include "db/genes-saver.h"
#include "db/genes-loader.h"
#include "db/pony-saver.h"
#include "db/scheme.h"

BOOST_AUTO_TEST_SUITE(gene)

BOOST_AUTO_TEST_CASE(gene_creation) {
	std::ignore = system("rm pony_test.db 2> /dev/null");
	
	DbConnection db = open_db("file:pony_test.db");
	run_scheme(db);
	GeneCategory::categories = load_all_genes_categories(db);

	Pony pony = create_pony(db, "Pinkie Pie");
	
	{
		auto& gc = create_gene_category(db);
		gc.recessive_stats.max_health = 100;
		gc.dominant_stats.max_health = 200;

		update_gene_category(db, gc);
	}

	{
		auto g = create_gene(db, GeneCategory::categories.at(1), pony);
		g.type = Gene::Type::aa;

		update_gene(db, g);
	}

	{
		auto g = load_gene(db, 1);
		BOOST_CHECK(g.type == Gene::Type::aa);

		BOOST_CHECK(g.get_stats_modifier().max_health == 100);

		g.type = Gene::Type::aA;
		BOOST_CHECK(g.get_stats_modifier().max_health == 200);

		g.type = Gene::Type::Aa;
		BOOST_CHECK(g.get_stats_modifier().max_health == 200);

		g.type = Gene::Type::AA;
		BOOST_CHECK(g.get_stats_modifier().max_health == 200);

		g.type = Gene::Type::aa;
		BOOST_CHECK(g.get_stats_modifier().max_health == 100);
	}

	std::ignore = system("rm pony_test.db 2> /dev/null");
}

BOOST_AUTO_TEST_CASE(gene_deletion) {
	std::ignore = system("rm pony_test.db 2> /dev/null");
	
	DbConnection db = open_db("file:pony_test.db");
	run_scheme(db);
	GeneCategory::categories = load_all_genes_categories(db);

	Pony pony = create_pony(db, "Pinkie Pie");
	
	create_gene_category(db);
	create_gene(db, GeneCategory::categories.at(1), pony);

	load_gene(db, 1);

	delete_gene(db, 1);

	BOOST_CHECK_THROW(load_gene(db, 1), std::runtime_error);

	std::ignore = system("rm pony_test.db 2> /dev/null");
}

BOOST_AUTO_TEST_SUITE_END()
