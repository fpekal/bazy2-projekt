#pragma once
#include <string>

class dbPony {
public:
	int id;
	std::string name;
};


class dbGeneCategory {
public:
	int id;
	std::string name;
};


class dbGene {
public:
	int id;
	std::string name;
	int category_id;
};


class dbPonyGene {
public:
	int id;
	int pony_id;
	int gene_id;
};
