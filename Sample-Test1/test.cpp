#include "pch.h"

#include "../소스.cpp"

#include <fstream>

TEST(SJ, getMatrixSize)
{
	constexpr const char* file_name = "test.txt";
	{
		std::ofstream out_file(file_name);
		out_file << "1.0 1.1 1.3 \n2.1 2.2 2.3";
	}

	std::ifstream read_file(file_name);
	MatrixSize result = getMatrixSize(file_name);

	EXPECT_EQ(result.rows, 2);
	EXPECT_EQ(result.cols, 3);
}

TEST(SJ, getMatrixSize2)
{
	constexpr const char* file_name = "test.txt";
	{
		std::ofstream out_file(file_name);
		out_file << "1.0 1.1 1.3 1.4 \n2.1 2.2 2.3 2.4\n3.1 3.2 3.3 3.4";
	}

	std::ifstream read_file(file_name);
	MatrixSize result = getMatrixSize(file_name);

	EXPECT_EQ(result.rows, 3);
	EXPECT_EQ(result.cols, 4);
}

TEST(SJ, temp1)
{
	constexpr const char* file_name = "test.txt";
	{
		std::ofstream out_file(file_name);
		out_file << "1.0 1.1 1.3\n2.1 2.2 2.3";
	}

	MatrixSize result = getMatrixSize(file_name);

	std::ifstream read_file(file_name);
	const int numValues = result.rows * result.cols;
	std::vector<double> vals(numValues);
	for (int i = 0; i < numValues; ++i)
		read_file >> vals[i];

	std::vector<double> ref = { 1.0, 1.1,1.3,2.1,2.2,2.3 };
	EXPECT_EQ(vals, ref);


	std::vector<double> subValues(5);


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