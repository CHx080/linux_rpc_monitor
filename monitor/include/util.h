#pragma once
#include <fstream>
#include <string>
#include <vector>

class File {
public:
  File(const char *file_path);
  bool readLine(std::vector<std::string> *res);

private:
  std::ifstream handle;
};