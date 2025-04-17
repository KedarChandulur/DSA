// Recurrence relation is:
// if i = 0 || j = 0      ---> 0
// else                   ---> max(E[i][j - 1], E[i - 1][j], E[i - 1][j - 1]) + E[i][j]

#include <iostream>
#include <sstream>

static const uint32_t rows = 5;
static const uint32_t cols = 5;

uint32_t MaximumProfit(uint32_t arr[rows][cols])
{
    uint32_t arrTemp[rows + 1][cols + 1] = { 0 };
 
    for (uint32_t i = 1; i <= rows; ++i)
    {
        for (uint32_t j = 1; j <= cols; ++j)
        {
            arrTemp[i][j] +=  std::max(std::max(arrTemp[i - 1][j], arrTemp[i][j - 1]), arrTemp[i - 1][j - 1]) + arr[i - 1][j - 1];
        }
    }

    std::cout << std::endl;

    std::cout << "Changed Matrix";

    std::cout << std::endl;

    for (uint32_t i = 1; i <= rows; ++i)
    {
        for (uint32_t j = 1; j <= cols; ++j)
        {
            std::cout << arrTemp[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return arrTemp[rows][cols];
}

int main()
{
    uint32_t array[rows][cols] = { 0 };

    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);

    for (uint32_t i = 0; i < rows; ++i)
    {
        for (uint32_t j = 0; j < cols; ++j)
        {
            if (!(iss >> array[i][j]))
            {
                std::cout << "Invalid input. Please enter integers separated by white space." << std::endl;
                return 1;
            }
        }
    }

    std::cout << std::endl;

    std::cout << "Original Matrix";

    std::cout << std::endl;

    for (uint32_t i = 0; i < rows; ++i)
    {
        for (uint32_t j = 0; j < cols; ++j)
        {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "Maximum Profit: " << MaximumProfit(array) << std::endl;
}
