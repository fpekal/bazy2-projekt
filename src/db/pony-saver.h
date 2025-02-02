#pragma once
#include <string>

#include "../pony.h"
#include "db-connection.h"

// Save pony in a database
// Pony must previously exist
void update_pony(DbConnection& db, const Pony& pony);

// Create pony in a database
// It's the only way to create a new pony.
// Newly created pony will have default statistics.
// If you want to change newly created pony's statistics,
// use update_pony with ID returned by this function.
//
// The only thing that can be set with this function in name,
// because there is constraint on uniqueness of pony names.
//
// Returns: Newly created pony
Pony create_pony(DbConnection& db, const std::string& name);

// Delete pony from a database
// Further usage of pony object with this ID will result in throwing a std::runtime_error.
void delete_pony(DbConnection& db, int id);
