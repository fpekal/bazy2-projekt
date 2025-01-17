#include <sqlite3.h>

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "db/db-connection.h"
#include "db/genes-loader.h"
#include "db/genes-saver.h"
#include "db/pony-loader.h"
#include "db/pony-saver.h"
#include "db/scheme.h"
#include "tui/draw-pony.h"
#include "tui/menu.h"

int main() {
	srand(time(nullptr));

	DbConnection& db = DbConnection::get_instance("file:pony.db");
	run_scheme(db);
	GeneCategory::categories = load_all_genes_categories(db);

	Menu menu;
	while (true) {
		menu.show_state();
		menu.change_state(db);
	}
}
