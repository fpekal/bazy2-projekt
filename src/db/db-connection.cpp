#include "db-connection.h"

DbConnection_impl::DbConnection_impl(const char* URI) {
	sqlite3_open_v2(URI, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI, nullptr);
}

DbConnection_impl::~DbConnection_impl() {
	sqlite3_close_v2(db);
}

sqlite3* DbConnection_impl::get() const {
	return db;
}

DbConnection open_db(const std::string& URI) {
	return std::make_shared<DbConnection_impl>(URI.c_str());
}
