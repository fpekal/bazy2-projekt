#pragma once
#include <vector>

#include "db-connection.h"
#include "../pony.h"

Pony load_pony(DbConnection db, const std::string& name);
Pony load_pony(DbConnection db, int id);

std::vector<Pony> load_all_ponies(DbConnection db);

//TODO: wyszukiwanie po statystykach?
