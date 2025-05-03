//#include <iostream>      // std::cout, std::cin
//#include <fstream>       // std::ifstream
//#include <sstream>       // std::istringstream
//#include <string>        // std::string
//#include <vector>        // std::vector
//#include <cstdio>        // sscanf
//#include <cstdlib>       // atof
//#include <cstring>       // strtok
//#include <limits>        // std::numeric_limits


#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>


std::vector<double>
makeTable(const std::string& file_name, MatrixSize& size_out)
{
    std::ifstream file(file_name);
    if (!file)
        throw std::runtime_error("file input error");

    std::vector<double> data_table;      
    std::string line;
    int cols_fixed = 0;
    int current_row = 0;

    while (std::getline(file, line))
    {
        ++current_row;                   
        std::istringstream iss(line);
        double value;
        int col_count_this_row = 0;

        while (iss >> value)             
        {
            data_table.push_back(value);
            ++col_count_this_row;
        }

        if (cols_fixed == 0)           
            cols_fixed = col_count_this_row;
    }

    size_out.rows = current_row;
    size_out.cols = cols_fixed;

    return data_table;                
}


struct MatrixSize {
    int rows{ 0 };
    int cols{ 0 };
};


//MatrixSize getMatrixSize(const std::string& filename)
//{
//    std::ifstream input(filename);
//    if (!input)
//        std::cout << "file input error";
//
//    std::string line;
//    double intRows = 0;
//    double intCols = 0;
//
//    while (std::getline(input, line)) {
//        std::istringstream iss(line);
//        double currentCols = 0;
//        double dummy;
//       
//        while (iss >> dummy)         // 공백(스페이스·탭) 구분 숫자 읽기
//            ++currentCols;
//
//        if (currentCols == 0)
//            continue;
//
//        if (intRows == 0)            // 첫 유효 행: 열 수 확정
//            intCols = currentCols;
//
//        ++intRows;
//    }
//
//    if (intRows == 0)
//        throw std::runtime_error("no numeric data found in file");
//
//    // 최종 반환 시 double 로 변환
//    return { static_cast<int>(intRows), static_cast<int>(intCols) };
//}


















































//
//int main()
//{
//    std::ifstream file("matrix.dat");
//    if (!file.is_open()) {
//        std::cerr << "file load error\n";
//    	return 1;
//    }
//
//    //데이터 읽기
//   //(1) argument 로 input, output 받아서 처리, argument 구분은 혹은 가능한 경우 input은 const로만 받아오기) -> OK.
//   //(2) 구조체로 만들기 ->..? 
//    if (!readRawMatrix(filename, Matrix_Size)) return 1;
//
//    std::cout << "행 = " << rows << ", 열 = " << cols << '\n';
//
//    //데이터 넣기
//    std::vector<double> matrix(rows * cols);
//
//    // 2차원 벡터 temp -> 1차원 벡터 
//    int index = 0;
//    for (int r = 0; r < rows; ++r) {
//        for (int c = 0; c < cols; ++c) {
//            matrix[index++] = temp[r][c];
//        }
//    }
//
//    for (int r = 0; r < rows; ++r) {
//        for (int c = 0; c < cols; ++c) {
//            std::cout << matrix[r * cols + c] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    file.close();
//    return 0;
//}

//
//int main()
//{
//	//파일 열기
//	std::ifstream file("matrix.dat");
//	if (!file.is_open()) {
//		std::cerr << "file load error\n";
//		return 1;
//	}
//
//    std::vector<std::vector<double>> temp;
//    std::string line;
//    int cols = 0;
//
//    while (std::getline(file, line)) {
//
//        std::stringstream ss(line);
//        std::vector<double> rowValues;
//        double value;
//
//        // 공백 기준으로 카운팅
//        while (ss >> value) {
//            rowValues.push_back(value);
//        }
//
//        if (temp.empty()) {
//            cols = static_cast<int>(rowValues.size());
//        }
//        
//        temp.push_back(rowValues);
//    }
//
//    if (temp.empty()) {
//        std::cerr << "Wrong data!!" << std::endl;
//        return 1;
//    }
//
//    int rows = static_cast<int>(temp.size());
//
//    std::cout << "row check! " << rows << ", column check! " << cols << std::endl;
//
//    //데이터 넣기
//    std::vector<double> matrix(rows * cols);
//
//    // 2차원 벡터 temp -> 1차원 벡터 
//    int index = 0;
//    for (int r = 0; r < rows; ++r) {
//        for (int c = 0; c < cols; ++c) {
//            matrix[index++] = temp[r][c];
//        }
//    }
//
//    for (int r = 0; r < rows; ++r) {
//        for (int c = 0; c < cols; ++c) {
//            std::cout << matrix[r * cols + c] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    file.close();
//    return 0;
//
//
//	//// Todo 1
//	//// 파일을 읽어서 크기(데이터 개수)를 알아오기
//	//// 이 기능을 활용해서 동일 크기 벡터 만들기
//	//// 동일 크기 벡터에 그 데이터 전부 저장해오기
//
//	//// Todo 2
//	//// 형이 원하는 구체적인 상황 가져오기
// f1 = a1*A + b1*B
// f2 = a1*A + c1*C +c2*C + c3*C...
// f3 = p*f1 + f2^q + d1*(f1+f2)
// 
// 조건에 맞는 a1, b1 을 database에서 look-up, 해당 조건과 근접한 데이터들만을 메모리에 들고 있기 (a1, b1은 데이터 방식이 비슷)
// c1은 DB 중간중간에 필요한 정보가 산개되어 있음.(어떻게 처리해야 좋은 방식인지 현재로써는 모르겠음)
//
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//	//// file1
//	//std::vector<double> matrix(1000, 0.0);
//
//	////질문 여기 까지는 메모리 사용X ?, close 전까지는 계속 열려있는 상태? // RAII 패턴 --> 생성 소멸과 함께 메모리를 관리하는 패턴
//	//std::vector<double> matrix(16, 0.0);
//
//	////data read
//	//fin >> matrix[0] >> matrix[1] >> matrix[2] >> matrix[3];
//	//// 뒤에 남은 데이터 혹은 개행 처리
//	//fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//
//
//
//	////getline practice
//	//{
//	//	std::string line;
//	//	std::getline(fin, line);
//	//	//std::cout << line;
//	//	std::istringstream is(line);
//	//	is >> matrix[4] >> matrix[5] >> matrix[6] >> matrix[7];
//	//}
//
//	////sscanf practice
//	//{
//	//	std::string line;
//	//	std::getline(fin, line);
//	//	double a, b, c, d;
//	//	sscanf_s(line.c_str(), "%lf %lf %lf %lf", &a, &b, &c, &d);
//	//	matrix[8] = a;
//	//	matrix[9] = b;
//	//	matrix[10] = c;
//	//	matrix[11] = d;
//	//}
//
//	//fin.close();
//	////파일에 중복 접근 및 충돌 발생하는 경우
//
//	////output test
//	//std::cout << "matrix output\n";
//	//for (int row = 0; row < 4; ++row) {
//	//	for (int col = 0; col < 4; ++col) {
//	//		std::cout << matrix[row * 4 + col] << " ";
//	//	}
//	//	std::cout << "\n";
//	//}
//
//	////std::cout << matrix[3];
//
//	//return 0;
//}