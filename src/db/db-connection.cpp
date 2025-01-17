#include "db-connection.h"
#include <memory>

std::unique_ptr<DbConnection> DbConnection::instance;
std::mutex DbConnection::mutex;

DbConnection& DbConnection::get_instance(const char* uri) {
	std::lock_guard<std::mutex> lock(mutex);
	if (instance == nullptr) {
		instance->instance = std::unique_ptr<DbConnection>(new DbConnection());
		sqlite3_open_v2(uri, &instance->db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI,
						nullptr);
		instance->uri = std::string(uri);
	}
	
	return *instance;
}

void DbConnection::reset_db() {
	instance = nullptr;
}

DbConnection::~DbConnection() { sqlite3_close_v2(db); }

sqlite3* DbConnection::get() const { return db; }

