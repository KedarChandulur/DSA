#include "iostream"
#include "cassert"

#include "CatalanTopDown.h"

CatalanTopDown::CatalanTopDown()
{
	std::cout << "\nWelcome to Catalan Top Down Program\n" << std::endl;
}

const uint32_t CatalanTopDown::Calculate(const uint32_t n) const
{
	if (n == 0)
	{
		return 1;
	}

	uint32_t sum = 0;

	for (uint32_t i = 1; i <= n; i++)
	{
		sum += this->Calculate(i - 1) * this->Calculate(n - i);
	}

	return sum;
}

void CatalanTopDown::GetInput(uint32_t& n) const
{
	std::cout << "Enter the n value catalan program\n";

	std::cin >> n;
}

const uint32_t CatalanTopDown::GetInput() const
{
	uint32_t n;

	std::cout << "Enter the n value catalan program\n";

	std::cin >> n;

	return n;
}

void CatalanTopDown::RunDemo() const
{
	const uint32_t value = this->GetInput();

	const uint32_t output = this->Calculate(value);

	std::cout << "\nNumber of Multiplications are: " << output << std::endl;
}