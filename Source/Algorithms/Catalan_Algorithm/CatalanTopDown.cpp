#include "iostream"
#include "cassert"

const uint32_t CatalanTopDown(const uint32_t n)
{
	if (n == 0)
	{
		return 1;
	}

	uint32_t sum = 0;

	for (uint32_t i = 1; i <= n; i++)
	{
		sum += CatalanTopDown(i - 1) * CatalanTopDown(n - i);
	}

	return sum;
}

void GetInput(uint32_t& n)
{
	std::cout << "Enter the n value catalan program\n";

	std::cin >> n;
}

int main()
{
	uint32_t value;

	GetInput(value);

	value = CatalanTopDown(value);

	std::cout << "\nNumber of Multiplications are: " << value << std::endl;

	return 0;
}