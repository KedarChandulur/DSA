#include <iostream>
#include <vector>

#include "CatalanTopDown.h"
#include "CatalanMemoized.h"
#include "MaxProfit.h"

#define CATALAN_TOP_DOWN_TEST false
#define CATALAN_MEMOIZED_TEST false
#define MAX_PROFIT_TEST true

int main()
{
    std::cout << "\nDSA Program Started Running..." << std::endl;

    // --- Catalan Top Down example ---

    #if CATALAN_TOP_DOWN_TEST
    {
        CatalanTopDown catalanTopDown;

	    const uint32_t value = catalanTopDown.GetInput();

	    const uint32_t output = catalanTopDown.Calculate(value);

	    std::cout << "\nNumber of Multiplications are: " << output << std::endl;
    }
    #endif

    // --- Catalan Top Down example ---


    // --- Catalan Memoized example ---

    #if CATALAN_MEMOIZED_TEST
    {
        CatalanMemoized catalanMemoized;

	    int32_t* arr = nullptr;
	    uint32_t value;

	    catalanMemoized.GetInput(arr, value);

	    value = catalanMemoized.Calculate(value, arr);

	    std::cout << "\nNumber of Multiplications are: " << value << std::endl;

	    delete[] arr;
	    arr = nullptr;
    }
    #endif

    // --- Catalan Memoized example ---


    // --- Max Profit example ---

    #if MAX_PROFIT_TEST
    {
        MaxProfit maxProfit;

        std::vector<std::vector<uint32_t>> arr;

        if(maxProfit.GetInput(arr))
        {
            maxProfit.PrintMatrix(arr, "Original Matrix");

            const uint32_t maximumProfit = maxProfit.Calculate(arr);
    
            std::cout << std::endl << "Maximum Profit: " << maximumProfit << std::endl;
        }
        else
        {
            std::cout << "\nMax profit program failed\n";
        }
    }
    #endif

    // --- Max Profit example ---

    std::cout << "\nDSA Program Complete..." << std::endl;

    return 0;
}