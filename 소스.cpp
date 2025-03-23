#include <iostream>      // std::cout, std::cin
#include <fstream>       // std::ifstream
#include <sstream>       // std::istringstream
#include <string>        // std::string
#include <vector>        // std::vector
#include <cstdio>        // sscanf
#include <cstdlib>       // atof
#include <cstring>       // strtok
#include <limits>        // std::numeric_limits

int main()
{
	//���� ����
	std::ifstream file("matrix.dat");
	if (!file.is_open()) {
		std::cerr << "file load error\n";
		return 1;
	}

    std::vector<std::vector<double>> temp;
    std::string line;
    int cols = 0;

    while (std::getline(file, line)) {

        std::stringstream ss(line);
        std::vector<double> rowValues;
        double value;

        // ���� �������� ī����
        while (ss >> value) {
            rowValues.push_back(value);
        }

        if (temp.empty()) {
            cols = static_cast<int>(rowValues.size());
        }
        
        temp.push_back(rowValues);
    }

    if (temp.empty()) {
        std::cerr << "Wrong data!!" << std::endl;
        return 1;
    }

    int rows = static_cast<int>(temp.size());

    std::cout << "row check! " << rows << ", column check! " << cols << std::endl;

    //������ �ֱ�
    std::vector<double> matrix(rows * cols);

    // 2���� ���� temp -> 1���� ���� 
    int index = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            matrix[index++] = temp[r][c];
        }
    }

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            std::cout << matrix[r * cols + c] << " ";
        }
        std::cout << std::endl;
    }

    file.close();
    return 0;


	//// Todo 1
	//// ������ �о ũ��(������ ����)�� �˾ƿ���
	//// �� ����� Ȱ���ؼ� ���� ũ�� ���� �����
	//// ���� ũ�� ���Ϳ� �� ������ ���� �����ؿ���

	//// Todo 2
	//// ���� ���ϴ� ��ü���� ��Ȳ ��������

	//// file1
	//std::vector<double> matrix(1000, 0.0);

	////���� ���� ������ �޸� ���X ?, close �������� ��� �����ִ� ����? // RAII ���� --> ���� �Ҹ�� �Բ� �޸𸮸� �����ϴ� ����
	//std::vector<double> matrix(16, 0.0);

	////data read
	//fin >> matrix[0] >> matrix[1] >> matrix[2] >> matrix[3];
	//// �ڿ� ���� ������ Ȥ�� ���� ó��
	//fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');




	////getline practice
	//{
	//	std::string line;
	//	std::getline(fin, line);
	//	//std::cout << line;
	//	std::istringstream is(line);
	//	is >> matrix[4] >> matrix[5] >> matrix[6] >> matrix[7];
	//}

	////sscanf practice
	//{
	//	std::string line;
	//	std::getline(fin, line);
	//	double a, b, c, d;
	//	sscanf_s(line.c_str(), "%lf %lf %lf %lf", &a, &b, &c, &d);
	//	matrix[8] = a;
	//	matrix[9] = b;
	//	matrix[10] = c;
	//	matrix[11] = d;
	//}

	//fin.close();
	////���Ͽ� �ߺ� ���� �� �浹 �߻��ϴ� ���

	////output test
	//std::cout << "matrix output\n";
	//for (int row = 0; row < 4; ++row) {
	//	for (int col = 0; col < 4; ++col) {
	//		std::cout << matrix[row * 4 + col] << " ";
	//	}
	//	std::cout << "\n";
	//}

	////std::cout << matrix[3];

	//return 0;
}