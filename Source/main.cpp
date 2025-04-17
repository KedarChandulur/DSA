#include <iostream>
#include "CatalanTopDown.h"

int main()
{
    std::cout << "Main is running" << std::endl;

    // --- Catalan Top Down example ---

    CatalanTopDown catalanTopDown;

	const uint32_t value = catalanTopDown.GetInput();

	const uint32_t output = catalanTopDown.Calculate(value);

	std::cout << "\nNumber of Multiplications are: " << output << std::endl;

    // --- Catalan Top Down example ---

    return 0;
}