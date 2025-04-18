#include <iostream>
#include <vector>
#include <cassert>

#include "CatalanTopDown.h"
#include "CatalanMemoized.h"
#include "MaxProfit.h"
#include "MinNoOfBills.h"
#include "BasicNumbersSort.h"

#define CATALAN_TOP_DOWN_TEST false
#define CATALAN_MEMOIZED_TEST false
#define MAX_PROFIT_TEST false
#define MIN_NO_OF_BILLS_TEST false
#define QUICK_SORT_TEST true

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


    // --- Min No Of Bills example ---

    #if MIN_NO_OF_BILLS_TEST
    {
        MinNoOfBills minNoOfBills;

        int target = 122;
        std::vector<int> denomination;

        if(minNoOfBills.GetInput(denomination, target))
        {
            const std::vector<int> solution = minNoOfBills.FindMinDenomination(target, denomination);
    
            std::cout << "\nMinimum number bills required: " << solution.size() << std::endl;
            std::cout << "Following is minimal number of bills for " << target << ": ";
            
            for (int i = 0; i < solution.size(); i++)
            {
                std::cout << solution[i] << " ";
            }
        
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\nMin No Of Bills program failed\n";
        }
    }
    #endif

    // --- Min No Of Bills example ---


    // --- Quick Sort example ---

    #if QUICK_SORT_TEST
    {
        BasicNumbersSort basicNumbersSort;

	    int32_t* A = nullptr;
	    int32_t n = 0;

	    basicNumbersSort.GetInput(A, n);

	    assert(A != nullptr);

	    printf("\nInput:\n");

	    for (int i = 0; i < n; ++i)
	    {
	    	printf("%d ", A[i]);
	    }

	    printf("\n");
    
	    basicNumbersSort.QuickSort(A, n);

	    printf("\nOutput:\n");

	    for (int i = 0; i < n; ++i)
	    {
	    	printf("%d ", A[i]);
	    }

	    printf("\n");

	    delete[] A;
	    A = nullptr;
    }
    #endif

    // --- Quick Sort example ---

    std::cout << "\nDSA Program Complete..." << std::endl;

    return 0;
}