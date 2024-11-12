#include "scheme.h"

#include <sqlite3.h>

#include "../util.h"

void run_scheme(DbConnection db) {
	sqlite3_exec(*db, load_entire_file("sql/make_scheme.sql").c_str(), nullptr, nullptr, nullptr);
}
