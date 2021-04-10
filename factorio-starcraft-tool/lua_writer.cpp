#include "lua_writer.h"

#include <string>
#include <map>
#include <any>
#include <vector>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <stdexcept>

std::string to_lua_string(const std::any& data, int indent = 0);
std::string to_lua_string(const std::vector<std::any>& data, int indent = 0);
std::string to_lua_string(const std::map<std::string, std::any>& data, int indent = 0);


std::string to_lua_string(const std::any& data, int indent) {
  if (const bool* v = std::any_cast<bool>(&data)) {
    return *v ? "true" : "false";
  }
  else if (const int* v = std::any_cast<int>(&data)) {
    return std::to_string(*v);
  }
  else if (const unsigned* v = std::any_cast<unsigned>(&data)) {
    return std::to_string(*v);
  }
  else if (const double* v = std::any_cast<double>(&data)) {
    return std::to_string(*v);
  }
  else if (const std::map<std::string, std::any>* v = std::any_cast<std::map<std::string, std::any>>(&data)) {
    return to_lua_string(*v, indent + 1);
  }
  else if (const std::vector<std::any>* v = std::any_cast<std::vector<std::any>>(&data)) {
    return to_lua_string(*v, indent + 1);
  }
  else if (const std::string* v = std::any_cast<std::string>(&data)) {
    return "\"" + *v + "\"";
  }
  std::string err = std::string("Unhandled type: ") + data.type().name();
  throw std::exception(err.c_str());
}

std::string to_lua_string(const std::vector<std::any>& data, int indent) {
  std::ostringstream ss;
  ss << "{ ";
  for (const std::any& v : data) {
    ss << to_lua_string(v, indent) << ", ";
  }
  ss << "}";
  return ss.str();
}

std::string to_lua_string(const std::map<std::string, std::any>& data, int indent) {
  std::ostringstream ss;
  ss << std::boolalpha;
  ss << "{\n";

  std::string spaces((indent + 1) * 2, ' ');
  for (auto& pair : data) {
    ss << spaces << pair.first << " = " << to_lua_string(pair.second, indent + 2) << ",\n";
  }
  ss << "}";
  return ss.str();
}

void write_lua_file(const std::string& filename, const std::map<std::string, std::any>& data) {
  std::ofstream of(filename);
  of << to_lua_string(data) << "\n";
}

