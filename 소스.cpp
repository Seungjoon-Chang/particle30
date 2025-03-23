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
	//파일 열기
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

        // 공백 기준으로 카운팅
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

    //데이터 넣기
    std::vector<double> matrix(rows * cols);

    // 2차원 벡터 temp -> 1차원 벡터 
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
	//// 파일을 읽어서 크기(데이터 개수)를 알아오기
	//// 이 기능을 활용해서 동일 크기 벡터 만들기
	//// 동일 크기 벡터에 그 데이터 전부 저장해오기

	//// Todo 2
	//// 형이 원하는 구체적인 상황 가져오기

	//// file1
	//std::vector<double> matrix(1000, 0.0);

	////질문 여기 까지는 메모리 사용X ?, close 전까지는 계속 열려있는 상태? // RAII 패턴 --> 생성 소멸과 함께 메모리를 관리하는 패턴
	//std::vector<double> matrix(16, 0.0);

	////data read
	//fin >> matrix[0] >> matrix[1] >> matrix[2] >> matrix[3];
	//// 뒤에 남은 데이터 혹은 개행 처리
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
	////파일에 중복 접근 및 충돌 발생하는 경우

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