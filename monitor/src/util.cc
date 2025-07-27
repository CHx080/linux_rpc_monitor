#include "util.h"
#include <sstream>

File::File(const char *file_path) : handle(file_path) {}

bool File::readLine(std::vector<std::string> *res) {
  std::string line, temp;
  std::getline(handle, line);
  if (res == nullptr) {
    return true;
  }
  std::istringstream striper(line);
  if (handle.eof()) {
    return false;
  }
  while (striper >> temp) {
    res->emplace_back(temp);
  }
  return true;
}