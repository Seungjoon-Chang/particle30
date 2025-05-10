#include "pch.h"

#include "../Project2/ms.h"

namespace
{
void make_table_file(const char* file_name, const uint32 num_rows, const uint32 num_cols, const std::vector<double>& datas);
}

TEST(ms, make_table)
{
  constexpr const char* file_name = "test.txt";
  constexpr uint32      num_rows  = 2;
  constexpr uint32      num_cols  = 3;
  std::vector<double>   datas     = {1.0, 1.1, 1.3, 2.1, 2.2, 2.3};
  make_table_file(file_name, num_rows, num_cols, datas);

  std::ifstream read_file(file_name);

  const Table result = make_table(read_file);
  const Table ref    = {num_rows, num_cols, std::move(datas)};

  EXPECT_EQ(result, ref);
}

TEST(ms, get_subtable_view)
{
  constexpr const char* file_name = "test.txt";
  constexpr uint32      num_rows  = 4;
  constexpr uint32      num_cols  = 3;
  std::vector<double>   datas     = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3, 4.1, 4.2, 4.3};
  make_table_file(file_name, num_rows, num_cols, datas);

  std::ifstream read_file(file_name);

  const Table      table  = make_table(read_file);
  const Table_View result = table.get_subtable_view(1, 3); // 2, 3 행을 가져온다;

  constexpr uint32    num_ref_rows = 2;
  constexpr uint32    num_ref_cols = num_cols;
  std::vector<double> ref_datas    = {2.1, 2.2, 2.3, 3.1, 3.2, 3.3};
  const Table_View    ref          = {num_ref_rows, num_ref_cols, ref_datas.data()};

  EXPECT_EQ(result, ref);
}

TEST(ms, get_subtable_view2)
{
  constexpr const char* file_name = "test.txt";
  constexpr uint32      num_rows  = 4;
  constexpr uint32      num_cols  = 3;
  std::vector<double>   datas     = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3, 4.1, 4.2, 4.3};
  make_table_file(file_name, num_rows, num_cols, datas);

  std::ifstream read_file(file_name);

  const Table                 table     = make_table(read_file);
  const std::optional<uint32> row_index = table.find_row_index(3.1);
  assert(row_index.has_value());

   // 3.1 로 시작하는 row 를 찾아서 위로 1줄, 아래로 1줄을 추가한 범위의 Table View 를 가져온다.
  const uint32     start_row = *row_index - 1;
  const uint32     end_row   = *row_index + 2;
  const Table_View result    = table.get_subtable_view(start_row, end_row);

  constexpr uint32    num_ref_rows = 3;
  constexpr uint32    num_ref_cols = num_cols;
  std::vector<double> ref_datas    = {2.1, 2.2, 2.3, 3.1, 3.2, 3.3, 4.1, 4.2, 4.3};
  const Table_View    ref          = {num_ref_rows, num_ref_cols, ref_datas.data()};

  EXPECT_EQ(result, ref);
}

TEST(ms, find_row_index1)
{
  constexpr const char* file_name = "test.txt";
  constexpr uint32      num_rows  = 4;
  constexpr uint32      num_cols  = 3;
  std::vector<double>   datas     = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3, 4.1, 4.2, 4.3};
  make_table_file(file_name, num_rows, num_cols, datas);

  std::ifstream read_file(file_name);

  const Table                 table     = make_table(read_file);
  const std::optional<uint32> row_index = table.find_row_index(3.1);
  EXPECT_EQ(*row_index, 2);
}
TEST(ms, find_row_index2)
{
  constexpr const char* file_name = "test.txt";
  constexpr uint32      num_rows  = 4;
  constexpr uint32      num_cols  = 3;
  std::vector<double>   datas     = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3, 4.1, 4.2, 4.3};
  make_table_file(file_name, num_rows, num_cols, datas);

  std::ifstream read_file(file_name);

  const Table                 table     = make_table(read_file);
  const std::optional<uint32> row_index = table.find_row_index(10.1);
  EXPECT_EQ(row_index, std::nullopt);
}

namespace
{
void make_table_file(const char* file_name, const uint32 num_rows, const uint32 num_cols, const std::vector<double>& datas)
{
  std::ofstream out_file(file_name);

  const uint32 last_row = num_rows - 1;
  const uint32 last_col = num_cols - 1;

  for (uint32 i = 0; i < num_rows; ++i)
  {
    for (uint32 j = 0; j < num_cols; ++j)
    {
      out_file << datas[i * num_cols + j];

      if (j != last_col)
        out_file << " ";
    }

    if (i != last_row)
      out_file << "\n";
  }
}

std::ostream& operator<<(std::ostream& os, const Table_View& table_view)
{
  os << "\n";
  os << table_view.to_string();
  return os;
}

} // namespace

// TEST(ms, make_talble_file)
//{
//   constexpr const char*     file_name = "test.txt";
//   constexpr uint32          num_rows  = 2;
//   constexpr uint32          num_cols  = 3;
//   const std::vector<double> datas     = {1.01, 1.1, 1.3, 2.1, 2.2, 2.3};
//   make_table_file(file_name, num_rows, num_cols, datas);
//
//   constexpr const char* file_name2 = "ref.txt";
//   {
//     std::ofstream out_file(file_name2);
//     out_file << "1.01 1.1 1.3\n2.1 2.2 2.3";
//   }
//
//   std::ifstream read_file(file_name, std::ios_base::binary);
//   std::ifstream read_file2(file_name2, std::ios_base::binary);
//
//   EXPECT_TRUE(std::equal(
//     std::istreambuf_iterator<char>(read_file),
//     std::istreambuf_iterator<char>(),
//     std::istreambuf_iterator<char>(read_file2)));
// }

TEST(ms, temp)
{
  std::istringstream iss;
  double             val;

  iss.str("1.0");
  iss >> val;

  EXPECT_FALSE(iss.fail());
  EXPECT_TRUE(iss.eof());

  iss.str("2.0");
  iss >> val;

  // EOF bit 가 켜져있어서 추출 실패
  EXPECT_TRUE(iss.fail());

  // 추출 실패로 값이 변하지 않는다.
  EXPECT_NE(val, 2.0);
  EXPECT_EQ(val, 1.0);
}