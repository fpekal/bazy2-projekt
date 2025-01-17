#pragma once
#include <map>
#include <vector>

#include "../genes.h"
#include "../pony.h"
#include "db-connection.h"

std::map<int, GeneCategory> load_all_genes_categories(DbConnection& db);

Gene load_gene(DbConnection& db, int id);

// Get genes that are assigned to the pony
std::vector<Gene> load_genes_of_pony(DbConnection& db, const Pony& pony);
