#pragma once
#include <string>

// Run linux command and return the stdout
std::string exec(const std::string& cmd);

// Adds "\x1b" to the beginning of the string
std::string add_ansi_esc(const std::string& str);

void save_cursor_position();
void restore_cursor_position();
void save_cursor_position2();
void restore_cursor_position2();

void move_cursor_to_left_edge();
void move_cursor_down(int amount = 1);
void move_cursor_right(int amount = 1);
void move_cursor_up(int amount = 1);
