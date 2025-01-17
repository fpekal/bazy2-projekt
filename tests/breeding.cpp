#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <stdlib.h>
#include <map>

#include "breeding.h"
#include "pony.h"
#include "db/pony-saver.h"
#include "db/scheme.h"
#include "db/genes-saver.h"
#include "db/genes-loader.h"
#include "db/pony-loader.h"

BOOST_AUTO_TEST_CASE(test_breeding) {
	std::ignore = system("rm pony_test.db 2> /dev/null");

	DbConnection& db = DbConnection::get_instance("file:pony_test.db");

	run_scheme(db);
    GeneCategory::categories = load_all_genes_categories(db);
    {
        auto& gc = create_gene_category(db);
        update_gene_category(db, gc);
    }

    GeneCategory::categories = load_all_genes_categories(db);
    const int iterations = 50;
    std::map<Gene::Type, int> results;

		{
			Pony parent1 = create_pony(db, "parent1");
			Pony parent2 = create_pony(db, "parent2");

			Gene gene1 = create_gene(db, GeneCategory::categories.at(1), parent1);
			gene1.type = Gene::Type::AA;
			update_gene(db, gene1);

			Gene gene2 = create_gene(db, GeneCategory::categories.at(1), parent2);
			gene2.type = Gene::Type::aa;
			update_gene(db, gene2);
		}

		{
			Pony parent1 = load_pony(db, "parent1");
			Pony parent2 = load_pony(db, "parent2");

			for (int i = 0; i < iterations; i++) {
					Pony child = breed(db, parent1, parent2, "test");
					results[child.genes.at(0).type]++;
					delete_pony(db, child.id);
			}


			BOOST_CHECK(results.size() == 1);
			BOOST_CHECK(results[Gene::Type::Aa] > 0);
			BOOST_CHECK(results[Gene::Type::aA] == 0);
			BOOST_CHECK(results[Gene::Type::AA] == 0);
			BOOST_CHECK(results[Gene::Type::aa] == 0);
		}

    results.clear();

		{
			Pony parent3 = create_pony(db, "parent3");
			Pony parent4 = create_pony(db, "parent4");

			{
					Gene gene1 = create_gene(db, GeneCategory::categories.at(1), parent3);
					gene1.type = Gene::Type::Aa;
					update_gene(db, gene1);

					Gene gene2 = create_gene(db, GeneCategory::categories.at(1), parent4);
					gene2.type = Gene::Type::Aa;
					update_gene(db, gene2);
			}
		}

		{
			Pony parent3 = load_pony(db, "parent3");
			Pony parent4 = load_pony(db, "parent4");

			for (int i = 0; i < iterations; i++) {
					Pony child = breed(db, parent3, parent4, "test");
					results[child.genes.at(0).type]++;
					delete_pony(db, child.id);
			}

			BOOST_CHECK(results.size() == 4);
			BOOST_CHECK(results[Gene::Type::Aa] > 0);
			BOOST_CHECK(results[Gene::Type::aA] > 0);
			BOOST_CHECK(results[Gene::Type::AA] > 0);
			BOOST_CHECK(results[Gene::Type::aa] > 0);
		}

	DbConnection::reset_db();
	std::ignore = system("rm pony_test.db 2> /dev/null");
}
