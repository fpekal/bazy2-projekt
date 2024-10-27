#include <iostream>
#include <fstream>
#include <sqlite3.h>

std::string load_scheme() {
	std::ifstream ifs("sql/make_scheme.sql");
	std::string sql((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	return sql;
}

int main() {
	sqlite3 *db;

	sqlite3_open_v2("file:pony.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI, nullptr);
	
	sqlite3_exec(db, load_scheme().c_str(), nullptr, nullptr, nullptr);

	sqlite3_close_v2(db);
}
