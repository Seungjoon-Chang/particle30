#include "pch.h"

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

	// ���� �Լ��� �ϴµ� 
	std::ofstream file1("test.txt");
	file1 << "abc";

	std::ifstream file2("test.txt");
	std::string str;
	file2 >> str;

	EXPECT_TRUE(file1.is_open());
	EXPECT_TRUE(file2.is_open());
}