#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <stdlib.h>

#include "pony.h"
#include "db/db-connection.h"
#include "db/scheme.h"
#include "db/pony-loader.h"
#include "db/pony-saver.h"

BOOST_AUTO_TEST_SUITE(pony)

BOOST_AUTO_TEST_CASE(pony_creation) {
	std::ignore = system("rm pony_test.db 2> /dev/null");
	DbConnection::reset_db();
	
	{
		DbConnection& db = DbConnection::get_instance("file:pony_test.db");
		run_scheme(db);

		Pony p = create_pony(db, "Pinkie Pie");

		p.health = 12;

		p.learned_stats.max_health = 10;
		p.learned_stats.min_damage = 1;
		p.learned_stats.max_damage = 2;
		p.learned_stats.attack_speed = 3;
		p.learned_stats.armor = 4;
		p.learned_stats.health_regeneration = 5;

		update_pony(db, p);
	}

	{
		DbConnection& db = DbConnection::get_instance("file:pony_test.db");
		Pony p = load_pony(db, "Pinkie Pie");
		BOOST_CHECK(p.health == 12);

		auto stats = p.get_effective_stats();

		BOOST_CHECK(stats.max_health == 10);
		BOOST_CHECK(stats.min_damage == 1);
		BOOST_CHECK(stats.max_damage == 2);
		BOOST_CHECK(stats.attack_speed == 3);
		BOOST_CHECK(stats.armor == 4);
		BOOST_CHECK(stats.health_regeneration == 5);
	}

	{
		DbConnection& db = DbConnection::get_instance("file:pony_test.db");
		Pony p = load_pony(db, 1);
		BOOST_CHECK(p.health == 12);

		auto stats = p.get_effective_stats();

		BOOST_CHECK(stats.max_health == 10);
		BOOST_CHECK(stats.min_damage == 1);
		BOOST_CHECK(stats.max_damage == 2);
		BOOST_CHECK(stats.attack_speed == 3);
		BOOST_CHECK(stats.armor == 4);
		BOOST_CHECK(stats.health_regeneration == 5);
	}

	std::ignore = system("rm pony_test.db 2> /dev/null");
	DbConnection::reset_db();
}

BOOST_AUTO_TEST_CASE(pony_deletion) {
	std::ignore = system("rm pony_test.db 2> /dev/null");
	DbConnection::reset_db();

	DbConnection& db = DbConnection::get_instance("file:pony_test.db");
	run_scheme(db);

	create_pony(db, "Pinkie Pie");
	load_pony(db, "Pinkie Pie");

	delete_pony(db, 1);

	BOOST_CHECK_THROW(load_pony(db, "Pinkie Pie"), std::runtime_error);

	std::ignore = system("rm pony_test.db 2> /dev/null");
	DbConnection::reset_db();
}

BOOST_AUTO_TEST_SUITE_END()
