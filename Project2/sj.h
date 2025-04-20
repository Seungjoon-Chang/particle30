#pragma once
#include "Common.h"

#include <fstream> // std::ifstream


Matrix_Size find_matrix_size_from_file(std::ifstream& file)
{
  Matrix_Size result;
  result.num_rows    = 1;
  result.num_columns = 2;
  return result;
};