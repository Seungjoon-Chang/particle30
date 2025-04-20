#pragma once

struct Matrix_Size
{
  int num_rows;
  int num_columns;

  bool operator==(const Matrix_Size& other) const
  {
    if ((num_rows == other.num_rows) && (num_columns == other.num_columns))
      return true;
    else
      return false;
  }
};
