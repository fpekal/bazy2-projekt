#pragma once
#include <sqlite3.h>

#include <memory>
#include <string>

// Explained in depth in documentation
class DbConnection_impl {
   public:
	DbConnection_impl(const char* URI);
	~DbConnection_impl();

	DbConnection_impl(const DbConnection_impl&) = delete;
	DbConnection_impl& operator=(const DbConnection_impl&) = delete;
	DbConnection_impl(DbConnection_impl&&) = delete;
	DbConnection_impl& operator=(DbConnection_impl&&) = delete;

	sqlite3* get() const;
	operator sqlite3*() const { return get(); }

   private:
	sqlite3* db;
};

typedef std::shared_ptr<DbConnection_impl> DbConnection;

DbConnection open_db(const std::string& URI);
