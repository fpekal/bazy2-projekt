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

int main() {
	DbConnection db = open_db("file:pony.db");

	run_scheme(db);
	
	auto gc = load_all_genes_categories(db);

	for (auto& [id, gc] : gc) {
		std::cout << id << ": " << gc.recessive_stats.max_damage << std::endl;
	}
	
	return 0;
}

