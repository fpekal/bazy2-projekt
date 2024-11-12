#include <iostream>
#include <fstream>
#include <string>

#include <sqlite3.h>

#include "db/db-connection.h"
#include "db/pony-loader.h"
#include "db/pony-saver.h"
#include "tui/ponysay.h"
#include "db/scheme.h"

int main() {
	ponysay("pinkiepie");

	DbConnection db = open_db("file:pony.db");

	run_scheme(db);
	
	{
		Pony p = create_pony(db, "Pony2");

		std::cout << p.name << '\n';

		p.name = "TEST";
		update_pony(db, p);
	}

	{
		Pony p = load_pony(db, 1);
		std::cout << p.name << std::endl;
	}

	try {
		Pony p = load_pony(db, "Pony2");
		std::cout << p.name << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\nAll ponies:\n";

	auto all_ponies = load_all_ponies(db);
	for (auto& pony : all_ponies) {
		std::cout << pony.name << std::endl;
	}

	delete_pony(db, all_ponies[0].id);

	all_ponies = load_all_ponies(db);
	std::cout << "Ponies after deletion: " << all_ponies.size() << std::endl;
}
