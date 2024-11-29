#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "db/db-connection.h"
#include "genes.h"
#include "db/genes-saver.h"
#include "db/genes-loader.h"
#include "db/scheme.h"

BOOST_AUTO_TEST_SUITE(gene_category)

BOOST_AUTO_TEST_CASE(gene_category_creation) {
	std::ignore = system("rm pony_test.db 2> /dev/null");
	
	DbConnection db = open_db("file:pony_test.db");
	run_scheme(db);
	GeneCategory::categories = load_all_genes_categories(db);
	
	{
		[[maybe_unused]]
		auto gc = create_gene_category(db);
		gc.recessive_stats.max_health = 100;
	}

	GeneCategory::categories = load_all_genes_categories(db);

	{
		auto gc = GeneCategory::categories.at(1);
		BOOST_CHECK(gc.recessive_stats.max_health == 0);

		gc.recessive_stats.max_health = 100;

		update_gene_category(db, gc);
	}

	GeneCategory::categories = load_all_genes_categories(db);

	{
		auto gc = GeneCategory::categories.at(1);
		BOOST_CHECK(gc.recessive_stats.max_health == 100);
	}

	std::ignore = system("rm pony_test.db 2> /dev/null");
}

BOOST_AUTO_TEST_CASE(gene_category_deletion) {
	std::ignore = system("rm pony_test.db 2> /dev/null");
	
	DbConnection db = open_db("file:pony_test.db");
	run_scheme(db);
	GeneCategory::categories = load_all_genes_categories(db);
	
	{
		auto gc = create_gene_category(db);
		gc.recessive_stats.max_health = 100;
		update_gene_category(db, gc);
	}

	GeneCategory::categories.at(1);

	delete_gene_category(db, 1);

	BOOST_CHECK_THROW(GeneCategory::categories.at(1), std::out_of_range);

	GeneCategory::categories = load_all_genes_categories(db);

	BOOST_CHECK_THROW(GeneCategory::categories.at(1), std::out_of_range);
	
	std::ignore = system("rm pony_test.db 2> /dev/null");
}

BOOST_AUTO_TEST_SUITE_END()
