#include <iostream>
#include <sstream>
#include <vector>

#include "MaxProfit.h"

// Recurrence relation is:
// if i = 0 || j = 0      ---> 0
// else                   ---> max(E[i][j - 1], E[i - 1][j], E[i - 1][j - 1]) + E[i][j]

MaxProfit::MaxProfit()
    :m_rows(5), m_cols(5)
{
	std::cout << "\nWelcome to Max Profit Program\n" << std::endl;
}

const bool MaxProfit::GetInput(std::vector<std::vector<uint32_t>>& arr)
{
    std::cout << "Enter no of rows:\n";

    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);

    if (!(iss >> m_rows))
    {
        std::cout << "Invalid input. Please enter a positive integer." << std::endl;
        return false;
    }

    std::cout << "Enter no of cols:\n";

    input.clear();
    std::getline(std::cin, input);
    iss.clear();
    iss.str(input);

    if (!(iss >> m_cols))
    {
        std::cout << "Invalid input. Please enter a positive integer." << std::endl;
        return false;
    }

    std::cout << "\nExample Input for 5 x 5 matrix: \n";
    std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 \n";

    std::cout << "\nYour input will be based on the matrix rows and cols you have entered: \n";

    std::cout << "Enter your input:\n";

    input.clear();
    std::getline(std::cin, input);
    iss.clear();
    iss.str(input);

    std::vector<std::vector<uint32_t>> temporary(m_rows, std::vector<uint32_t>(m_cols));

    for (uint32_t i = 0; i < m_rows; ++i)
    {
        for (uint32_t j = 0; j < m_cols; ++j)
        {
            if (!(iss >> temporary[i][j]))
            {
                std::cout << "Invalid input. Please enter integers separated by white space." << std::endl;
                return false;
            }
        }
    }

    arr = std::move(temporary);

    return true;
}

const uint32_t MaxProfit::Calculate(const std::vector<std::vector<uint32_t>>& arr) const
{
    const uint32_t rows = m_rows + 1;
    const uint32_t cols = m_cols + 1;
 
    std::vector<std::vector<uint32_t>> arrTemp(rows, std::vector<uint32_t>(cols, 0));

    for (uint32_t i = 1; i < rows; ++i)
    {
        for (uint32_t j = 1; j < cols; ++j)
        {
            arrTemp[i][j] +=  std::max(std::max(arrTemp[i - 1][j], arrTemp[i][j - 1]), arrTemp[i - 1][j - 1]) + arr[i - 1][j - 1];
        }
    }

    this->PrintMatrix(arrTemp, "Solution Matrix", rows, cols);

    return arrTemp[m_rows][m_cols];
}

void MaxProfit::PrintMatrix(const std::vector<std::vector<uint32_t>>& arr, const char* message, uint32_t rows, uint32_t cols) const
{
    rows = (rows == 0) ? m_rows : rows;
    cols = (cols == 0) ? m_cols : cols;

    std::cout << std::endl;
    std::cout << message;
    std::cout << std::endl;

    for (uint32_t i = 0; i < rows; ++i)
    {
        for (uint32_t j = 0; j < cols; ++j)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void MaxProfit::RunDemo()
{
    std::vector<std::vector<uint32_t>> arr;

    if(this->GetInput(arr))
    {
        this->PrintMatrix(arr, "Original Matrix");
        
        const uint32_t maximumProfit = this->Calculate(arr);

        std::cout << std::endl << "Maximum Profit: " << maximumProfit << std::endl;
    }
    else
    {
        std::cout << "\nMax profit program failed\n";
    }
}