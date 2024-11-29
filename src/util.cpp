#include "util.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>

std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, int(*)(FILE*)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string load_entire_file(const std::string& path) {
		std::ifstream t(path);
		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		return str;
}

std::string add_ansi_esc(const std::string& str) {
	return std::string{ "\x1b" } + str;
}

void save_cursor_position() {
	std::cout << add_ansi_esc("7") << std::flush;
}

void restore_cursor_position() {
	std::cout << add_ansi_esc("8") << std::flush;
}

void save_cursor_position2() {
	std::cout << add_ansi_esc("[s") << std::flush;
}

void restore_cursor_position2() {
	std::cout << add_ansi_esc("[u") << std::flush;
}

void move_cursor_to_left_edge() {
	std::cout << add_ansi_esc("[0G") << std::flush;
}

void move_cursor_down(int amount) {
	std::cout << add_ansi_esc(std::string{ "[" } + std::to_string(amount) + "B") << std::flush;
}

void move_cursor_right(int amount) {
	std::cout << add_ansi_esc(std::string{ "[" } + std::to_string(amount) + "C") << std::flush;
}

void move_cursor_up(int amount) {
	std::cout << add_ansi_esc(std::string{ "[" } + std::to_string(amount) + "A") << std::flush;
}
