#pragma once
#include "db-connection.h"
#include "../genes.h"

void update_gene_category(DbConnection db, const GeneCategory& gc);
//void update_gene(DbConnection db, const Gene& gene);

GeneCategory& create_gene_category(DbConnection db);

void delete_gene_category(DbConnection db, int id);
