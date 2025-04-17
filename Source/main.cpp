#include <iostream>
#include "CatalanTopDown.h"
#include "CatalanMemoized.h"

#define CATALAN_TOP_DOWN false
#define CATALAN_MEMOIZED true

int main()
{
    std::cout << "\nDSA Program Started Running..." << std::endl;

    // --- Catalan Top Down example ---

    #if CATALAN_TOP_DOWN
    {
        CatalanTopDown catalanTopDown;

	    const uint32_t value = catalanTopDown.GetInput();

	    const uint32_t output = catalanTopDown.Calculate(value);

	    std::cout << "\nNumber of Multiplications are: " << output << std::endl;
    }
    #endif

    // --- Catalan Top Down example ---


    // --- Catalan Memoized example ---

    #if CATALAN_MEMOIZED
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

    std::cout << "\nDSA Program Complete..." << std::endl;

    return 0;
}