#include <iostream>
#include <fstream>
#include <sqlite3.h>

#include "db/db-connection.h"

std::string load_scheme() {
	std::ifstream ifs("sql/make_scheme.sql");
	std::string sql((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	return sql;
}

int main() {
	DbConnection db = open_db("file:pony.db");
	DbConnection db2 = db;

	sqlite3_exec(*db2, load_scheme().c_str(), nullptr, nullptr, nullptr);
}
