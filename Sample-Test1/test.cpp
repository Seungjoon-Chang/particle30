#include "pch.h"

#include "../Project2/ms.h"
#include "../소스.cpp"

#include <fstream>

TEST(TestCaseName, TestName)
{
  std::ifstream file1("matrix.dat");
  std::ifstream file2("matrix.dat");

  EXPECT_TRUE(file1.is_open());
  EXPECT_TRUE(file2.is_open());
}

TEST(TestCaseName, TestName2)
{
  std::ofstream file1("matrix.dat");
  std::ifstream file2("matrix.dat");

  EXPECT_TRUE(file1.is_open());
  EXPECT_TRUE(file2.is_open());
}

TEST(TestCaseName, TestName3)
{

  // 쓰는 함수를 하는데
  std::ofstream file1("test.txt");
  file1 << "abc";

  std::ifstream file2("test.txt");
  std::string   str;
  file2 >> str;

  EXPECT_TRUE(file1.is_open());
  EXPECT_TRUE(file2.is_open());
}

TEST(ms, estimate_size)
{
  constexpr const char* file_name = "test.txt";
  {
    std::ofstream out_file(file_name);
    out_file << "1.0 1.1 1.3 \n2.1 2.2 2.3";
  }

  std::ifstream     read_file(file_name);
  const Matrix_Size result = estimate_size(read_file);
  const Matrix_Size ref    = {2, 3};

  EXPECT_EQ(result, ref);
}