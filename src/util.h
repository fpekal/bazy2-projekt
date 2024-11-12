#pragma once
#include <string>

// Run linux command and return the stdout
std::string exec(const std::string& cmd);

// Load the entire file to a string
std::string load_entire_file(const std::string& path);
