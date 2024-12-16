#pragma once
#include <string>

#include "pony.h"

class Fight {
public:
	Fight(const Pony& pony1, const Pony& pony2) : left_pony(pony1), right_pony(pony2) {};

	Pony left_pony;
	Pony right_pony;
	int waiting_left = 0;
	int waiting_right = 0;

	enum Direction { LEFT, RIGHT, DRAW };

	Direction fight();
	void make_turn();

private:
	void make_turn(Pony& attacking, Pony& defending);
};
