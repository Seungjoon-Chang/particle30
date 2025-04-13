#include "pch.h"

#include "../소스.cpp"

#include <fstream>

TEST(TestCaseName, TestName) {
	std::ifstream file1("matrix.dat");
	std::ifstream file2("matrix.dat");

	EXPECT_TRUE(file1.is_open());
	EXPECT_TRUE(file2.is_open());
}

TEST(TestCaseName, TestName2) {
	std::ofstream file1("matrix.dat");
	std::ifstream file2("matrix.dat");

	EXPECT_TRUE(file1.is_open());
	EXPECT_TRUE(file2.is_open());
}

TEST(TestCaseName, TestName3) {

	// 쓰는 함수를 하는데 
	std::ofstream file1("test.txt");
	file1 << "abc";

	std::ifstream file2("test.txt");
	std::string str;
	file2 >> str;

	EXPECT_TRUE(file1.is_open());
	EXPECT_TRUE(file2.is_open());
}

TEST(Name1, Name2)
{
	const int result = test();
	constexpr int reference = 1;
	EXPECT_EQ(result, reference);
}

TEST(Name1, Name3)
{
	constexpr const char* file_name = "test.txt";
	{
		std::ofstream out_file(file_name);
		out_file << "1.0 1.1 1.3 \n2.1 2.2 2.3";
	}

	std::ifstream read_file(file_name);
	Matrix_Size result = { 2,3 };

	const int num_values = result.num_rows * result.num_columns;
	std::vector<double> values(num_values); //3번 

	for (int i = 0; i < num_values; ++i)
		read_file >> values[i];

	int debug = 0;

	//const Matrix_Size result = find_matrix_size_from_file(read_file);
	//constexpr Matrix_Size reference = { 3,4 };
	//EXPECT_EQ(result, reference);
}

//
//
//TEST(tem, find_matrix_size_from_file_test1)
//{
//	std::ifstream f("name");
//
//	Matrix_Size result = find_matrix_size_from_file(f);
//	
//
//
//	EXPECT_EQ(result.num_rows, 3);
//	EXPECT_EQ(result.num_cols, 5);
//
//
//
//	// ifstrem 객체 만들고
//	// find_matrix_size_from_file(ifstream)
//
//}