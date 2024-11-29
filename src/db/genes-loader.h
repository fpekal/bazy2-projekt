#pragma once
#include <map>

#include "db-connection.h"
#include "../genes.h"

std::map<int, GeneCategory> load_all_genes_categories(DbConnection db);

Gene load_gene(DbConnection db, int id);
