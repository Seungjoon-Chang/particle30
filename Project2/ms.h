#pragma once
#include <algorithm>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using uint32 = unsigned int;

class Table_View
{
public:
  Table_View(const uint32 num_rows, const uint32 num_cols, const double* data)
    : _num_rows(num_rows), _num_cols(num_cols), _data(data) {}

  bool operator==(const Table_View& other) const;

  std::string to_string(void) const;

private:
  uint32        _num_rows;
  uint32        _num_cols;
  const double* _data;
};

class Table
{
public:
  Table(const uint32 num_rows, const uint32 num_cols, std::vector<double>&& datas)
    : _num_rows(num_rows), _num_cols(num_cols), _datas(datas) {}

public:
  bool operator==(const Table& other) const;

  operator Table_View(void) const;

  std::optional<uint32> find_row_index(const double value) const;
  Table_View            get_subtable_view(const uint32 start_row, const uint32 end_row) const; // [start_row, end_row)

private:
  uint32              _num_rows;
  uint32              _num_cols;
  std::vector<double> _datas;
};

Table make_table(std::ifstream& file);