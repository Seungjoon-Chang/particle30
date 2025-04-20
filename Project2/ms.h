#pragma once
#include "Common.h"

#include <fstream> // std::ifstream
#include <string>
#include <algorithm>

using uint32 = unsigned int;


Matrix_Size estimate_size(std::ifstream& file)
{
  constexpr char space = ' ';

  std::string temp_line;
  std::getline(file, temp_line); // row 를 알아내야 됨

  const uint32 num_columns = static_cast<uint32>(std::count(temp_line.begin(), temp_line.end(), space));

  uint32 num_rows = 1;
  while (std::getline(file, temp_line))
    num_rows++;

  Matrix_Size result;
  result.num_rows    = num_rows;
  result.num_columns = num_columns;
  return result;
};