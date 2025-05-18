#include "sj.h"

Table makeTable(const std::string& file_name)
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

}