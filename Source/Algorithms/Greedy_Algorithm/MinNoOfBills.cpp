#include <iostream>
#include <vector>

// Recursive function to find minimum number of denominations
// Make sure your array is arranged/sorted in descending order.
void internalFindMinDenomination(const int target, const std::vector<int>& denomination, std::vector<int>& solution)
{
	// Recursive case: find the largest denomination that is less than or equal to target
	// and add it to the solution, and then recursively find the minimum number of denominations
	// for the remaining amount: target - denomination
	int temp = denomination[0]; // temp holds max denomination

	for (int i = 0; i < denomination.size(); i++)
	{
		if (denomination[i] <= target)
		{
			temp = denomination[i]; // temp holds max denomination
			break;
		}
	}

	solution.emplace_back(temp); // pushing max denomination

	temp = target - temp; // temp Finds and hold next target

	if (temp > 0)
	{
		internalFindMinDenomination(temp, denomination, solution);
	}
}

const std::vector<int> FindMinDenomination(const int target, const std::vector<int>& denomination)
{
	std::vector<int> denominationCopy(denomination);
	std::reverse(denominationCopy.begin(), denominationCopy.end());

	std::vector<int> solution;
	solution.reserve(denomination.size());

	internalFindMinDenomination(target, denominationCopy, solution);

	return solution;
}

const std::vector<int> FindMinDenomination(const int target, std::vector<int>& denomination)
{
	std::reverse(denomination.begin(), denomination.end());

	std::vector<int> solution;
	solution.reserve(denomination.size());

	internalFindMinDenomination(target, denomination, solution);

	return solution;
}

int main()
{
	int target = 122;

	std::cout << "Enter your target: ";
	std::cin >> target;

	const std::vector<int> denomination = { 1, 4, 7, 13, 28, 52, 91, 365 };

	const std::vector<int> solution = FindMinDenomination(target, denomination);

	std::cout << "Minimum number bills required: " << solution.size() << std::endl;
	std::cout << "Following is minimal number of bills for " << target << ": ";

	for (int i = 0; i < solution.size(); i++)
	{
		std::cout << solution[i] << " ";
	}

	std::cout << std::endl;

	return 0;
}