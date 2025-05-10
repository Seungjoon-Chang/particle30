#include "ms.h"

#include <cassert>
#include <iomanip>
#include <iostream>

//
// Table_View
//

bool Table_View::operator==(const Table_View& other) const
{
  if ((_num_rows != other._num_rows) || (_num_cols != other._num_cols))
    return false;

  const uint32 num_datas = _num_rows * _num_cols;
  if (std::equal(_data, _data + num_datas, other._data, other._data + num_datas))
    return true;
  else
    return false;
}

std::string Table_View::to_string(void) const
{
  std::ostringstream oss;
  oss << std::setprecision(16) << std::showpoint << std::left;

  const double* data = _data;
  for (uint32 i = 0; i < _num_rows; ++i)
  {
    for (uint32 j = 0; j < _num_cols; ++j)
      oss << std::setw(25) << data[j];

    oss << "\n";
    data += _num_cols;
  }

  return oss.str();
}

//
// Table
//

bool Table::operator==(const Table& other) const
{
  if ((_num_rows != other._num_rows) || (_num_cols != other._num_cols))
    return false;

  if (std::equal(_datas.begin(), _datas.end(), other._datas.begin(), other._datas.end()))
    return true;
  else
    return false;
}

Table::operator Table_View(void) const
{
  return Table_View(_num_rows, _num_cols, _datas.data());
}

Table_View Table::get_subtable_view(const uint32 start_row, const uint32 end_row) const
{
  const uint32  num_rows = end_row - start_row;
  const double* data     = _datas.data() + start_row * _num_cols;

  Table_View result(num_rows, _num_cols, data);
  return result;
}

std::optional<uint32> Table::find_row_index(const double value) const
{
  const double* data = _datas.data();
  for (uint32 i = 0; i < _num_rows; ++i)
  {
    if (*data == value)
      return i;

    data += _num_cols;
  }

  return std::nullopt;
}

//
// Global Functions
//

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