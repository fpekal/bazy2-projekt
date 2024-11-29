#pragma once
#include "stats.h"

class GeneCategory {
public:
	GeneCategory() = delete;
	GeneCategory(const GeneCategory&) = default;
	GeneCategory(GeneCategory&&) = default;

	GeneCategory& operator=(const GeneCategory&) = delete;
	GeneCategory& operator=(GeneCategory&&) = delete;

	const int id;

	Stats recessive_stats;
	Stats dominant_stats;
};

class Gene {
public:
	Gene() = delete;
	Gene(const Gene&) = default;
	Gene(Gene&&) = default;

	Gene& operator=(const Gene&) = delete;
	Gene& operator=(Gene&&) = delete;

	const int id;
	const GeneCategory& category;

	enum Type {
		aa,aA,Aa,AA
	} type;
};
