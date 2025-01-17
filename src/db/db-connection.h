#pragma once
#include <sqlite3.h>

#include <memory>
#include <mutex>
#include <string>

// Explained in depth in documentation
class DbConnection {
   public:
	static DbConnection& get_instance(const char* uri);
	// for testing
	static void reset_db();
	~DbConnection();

	DbConnection(DbConnection& other) = delete;
	DbConnection(const DbConnection&) = delete;
	DbConnection& operator=(const DbConnection&) = delete;
	DbConnection(DbConnection&&) = delete;
	DbConnection& operator=(DbConnection&&) = delete;

	sqlite3* get() const;
	operator sqlite3*() const { return get(); }

   private:
	sqlite3* db;
	std::string uri;
	static std::mutex mutex;
	static std::unique_ptr<DbConnection> instance;

protected:
	DbConnection() { }
};
