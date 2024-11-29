#pragma once
#include "db-connection.h"
#include "../genes.h"

void update_gene_category(DbConnection db, const GeneCategory& gc);
GeneCategory& create_gene_category(DbConnection db);
void delete_gene_category(DbConnection db, int id);

void update_gene(DbConnection db, const Gene& gene);
Gene create_gene(DbConnection db, const GeneCategory& gc);
void delete_gene(DbConnection db, int id);
