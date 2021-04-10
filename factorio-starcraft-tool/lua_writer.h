#pragma once
#include <string>
#include <map>
#include <any>

void write_lua_file(const std::string& filename, const std::map<std::string, std::any>& data);
