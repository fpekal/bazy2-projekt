#include "ponysay.h"

#include <iostream>

#include "../util.h"

void ponysay(const std::string& pony_name) {
	std::string cmd = "ponysay -o -f " + pony_name;
	std::cout << exec(cmd);
}
