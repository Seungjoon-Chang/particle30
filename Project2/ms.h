#pragma once
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using uint32 = unsigned int;

class Table_View
{
public:
  Table_View(const uint32 num_rows, const uint32 num_cols, const double* data)
    : _num_rows(num_rows), _num_cols(num_cols), _data(data) {}

  bool operator==(const Table_View& other) const
  {
    if ((_num_rows != other._num_rows) || (_num_cols != other._num_cols))
      return false;

    const uint32 num_datas = _num_rows * _num_cols;
    if (std::equal(_data, _data + num_datas, other._data, other._data + num_datas))
      return true;
    else
      return false;
  }

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
  bool operator==(const Table& other) const
  {
    if ((_num_rows != other._num_rows) || (_num_cols != other._num_cols))
      return false;

    if (std::equal(_datas.begin(), _datas.end(), other._datas.begin(), other._datas.end()))
      return true;
    else
      return false;
  }

  operator Table_View(void) const
  {
    return Table_View(_num_rows, _num_cols, _datas.data());
  }

  // [start_row, end_row) 
  Table_View get_subtable_view(const uint32 start_row, const uint32 end_row) const
  {
    const uint32  num_rows = end_row - start_row;
    const double* data     = _datas.data() + start_row * _num_cols;

    Table_View result(num_rows, _num_cols, data);
    return result;
  }

private:
  uint32              _num_rows;
  uint32              _num_cols;
  std::vector<double> _datas;
};

Table make_table(std::ifstream& file)
{
  std::istringstream temp_stream;
  std::string        temp_str;

  double              data = 0.0;
  std::vector<double> datas;

  uint32 num_rows = 0;
  while (std::getline(file, temp_str))
  {
    temp_stream.clear();
    temp_stream.str(std::move(temp_str));

    while (temp_stream >> data)
      datas.push_back(data);

    num_rows++;
  }

  const uint32 num_data = static_cast<uint32>(datas.size());
  const uint32 num_cols = num_data / num_rows;

  Table table(num_rows, num_cols, std::move(datas));
  return table;
}