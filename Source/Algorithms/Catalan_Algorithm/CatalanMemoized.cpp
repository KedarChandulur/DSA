#include "iostream"
#include "cassert"

#include "CatalanMemoized.h"

CatalanMemoized::CatalanMemoized()
{
	std::cout << "\nWelcome to Catalan Memoized Program\n" << std::endl;
}

const uint32_t CatalanMemoized::Calculate(const uint32_t n, int32_t arr[]) const
{
	if (n == 0)
	{
		return 1;
	}

	if (arr[n] != -1)
	{
		return arr[n];
	}

	uint32_t sum = 0;

	for (uint32_t i = 1; i <= n; i++)
	{
		sum += this->Calculate(i - 1, arr) * this->Calculate(n - i, arr);
	}

	arr[n] = sum;

	return sum;
}

void CatalanMemoized::GetInput(int32_t*& A, uint32_t& n) const
{
	std::cout << "Enter the n value catalan program\n";

	std::cin >> n;

	A = new int32_t[n + 1]();

	assert(A != nullptr);

	memset(A, -1, (size_t)(n + 1) * sizeof(*A));
}

void CatalanMemoized::RunDemo() const
{
	int32_t* arr = nullptr;
	uint32_t value;

	this->GetInput(arr, value);
	value = this->Calculate(value, arr);

	std::cout << "\nNumber of Multiplications are: " << value << std::endl;
	
	delete[] arr;
	arr = nullptr;
}