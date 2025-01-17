#pragma once
#include "db/db-connection.h"
#include "pony.h"

Pony breed(DbConnection& db, const Pony& parent1, const Pony& parent2, const std::string& new_name);
