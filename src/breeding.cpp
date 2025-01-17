#include "breeding.h"

#include "db/genes-saver.h"
#include "db/pony-loader.h"
#include "db/pony-saver.h"

static Gene::Type random_type(const Gene::Type& parent1, const Gene::Type& parent2) {
	bool p1_dominant = false;
	switch (parent1) {
		case Gene::Type::aA:
			[[fallthrough]];
		case Gene::Type::Aa:
			p1_dominant = rand() % 2;
			break;
		case Gene::Type::AA:
			p1_dominant = true;
			break;
		case Gene::Type::aa:
			p1_dominant = false;
			break;
	}

	bool p2_dominant = false;
	switch (parent2) {
		case Gene::Type::aA:
			[[fallthrough]];
		case Gene::Type::Aa:
			p2_dominant = rand() % 2;
			break;
		case Gene::Type::AA:
			p2_dominant = true;
			break;
		case Gene::Type::aa:
			p2_dominant = false;
			break;
	}

	if (p1_dominant && p2_dominant)
		return Gene::Type::AA;
	else if (p1_dominant)
		return Gene::Type::Aa;
	else if (p2_dominant)
		return Gene::Type::aA;
	else
		return Gene::Type::aa;
}

static void merge_genes(DbConnection& db, Pony& child, const Pony& parent1, const Pony& parent2) {
	for (auto& gene1 : parent1.genes) {
		for (auto& gene2 : parent2.genes) {
			if (gene1.category.id == gene2.category.id) {
				auto gene = create_gene(db, gene1.category, child);

				gene.type = random_type(gene1.type, gene2.type);
				update_gene(db, gene);
			}
		}
	}
}

Pony breed(DbConnection& db, const Pony& parent1, const Pony& parent2, const std::string& new_name) {
	Pony child = create_pony(db, new_name);
	merge_genes(db, child, parent1, parent2);

	return load_pony(db, child.id);
}
