#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>

#include "MinNoOfBills.h"

MinNoOfBills::MinNoOfBills()
{
	std::cout << "\nWelcome to Min No Of Bills Program\n" << std::endl;
}

// Recursive function to find minimum number of denominations
// Make sure your array is arranged/sorted in descending order.
void MinNoOfBills::internalFindMinDenomination(const int target, const std::vector<int>& denominations, std::vector<int>& solution) const
{
	// Recursive case: find the largest denomination that is less than or equal to target
	// and add it to the solution, and then recursively find the minimum number of denominations
	// for the remaining amount: target - denomination
	int temp = denominations.front(); // temp holds max denomination

	for (int i = 0; i < denominations.size(); i++)
	{
		if (denominations[i] <= target)
		{
			temp = denominations[i]; // temp holds max denomination
			break;
		}
	}

	solution.emplace_back(temp); // pushing max denomination

	temp = target - temp; // temp Finds and hold next target

	if (temp > 0)
	{
		internalFindMinDenomination(temp, denominations, solution); // While loop can also be use instead of recursion.
	}
}

const std::vector<int> MinNoOfBills::FindMinDenomination(const int target, const std::vector<int>& denominations) const
{
	std::vector<int> denominationsCopy(denominations);
	
	std::sort(denominationsCopy.begin(), denominationsCopy.end(), std::greater<int>());

	std::vector<int> solution;
	solution.reserve(denominationsCopy.size());

	internalFindMinDenomination(target, denominationsCopy, solution);

	return solution;
}

const bool MinNoOfBills::GetInput(std::vector<int>& denominations, int& target) const
{
	std::cout << "\nExample Input for target: \n";
    std::cout << "122\n";

	std::cout << "Enter your target:\n";

    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);

    if (!(iss >> target))
    {
        std::cout << "Invalid input. Please enter a positive integer." << std::endl;
        return false;
    }

	std::cout << "\nExample Input for denomination size: \n";
    std::cout << "8\n";

    std::cout << "Enter your denomination size:\n";

    input.clear();
    std::getline(std::cin, input);
    iss.clear();
    iss.str(input);

	uint32_t denominationSize = 0;
	
    if (!(iss >> denominationSize))
    {
        std::cout << "Invalid input. Please enter the size again." << std::endl;
        return false;
    }

	std::cout << "\nExample Input for denomination values: \n";
    std::cout << "1 4 7 13 28 52 91 365 \n";

    std::cout << "Enter your denomination values:\n";

	input.clear();
    std::getline(std::cin, input);
    iss.clear();
    iss.str(input);

	denominations.resize(denominationSize);

    for (uint32_t i = 0; i < denominationSize; ++i)
    {
        if (!(iss >> denominations[i]))
        {
            std::cout << "Invalid input. Please enter integers separated by white space." << std::endl;
            return false;
        }
    }

    return true;
}