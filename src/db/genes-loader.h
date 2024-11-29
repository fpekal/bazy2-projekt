#pragma once
#include <map>
#include <vector>

#include "db-connection.h"
#include "../genes.h"
#include "../pony.h"

std::map<int, GeneCategory> load_all_genes_categories(DbConnection db);

Gene load_gene(DbConnection db, int id);
std::vector<Gene> load_genes_for_pony(DbConnection db, const Pony& pony);