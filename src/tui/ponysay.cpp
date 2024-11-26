#include "ponysay.h"

#include <iostream>

#include "../util.h"

std::string ponysay(const std::string& pony_name) {
	std::string cmd = "ponysay -o -F " + pony_name;
	return exec(cmd);
}
