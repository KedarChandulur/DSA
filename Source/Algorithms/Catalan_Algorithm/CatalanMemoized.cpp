#include "iostream"
#include "cassert"

const uint32_t CatalanMemoized(const uint32_t n, int32_t arr[])
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
		sum += CatalanMemoized(i - 1, arr) * CatalanMemoized(n - i, arr);
	}

	arr[n] = sum;

	return sum;
}

void GetInput(int32_t*& A, uint32_t& n)
{
	std::cout << "Enter the n value catalan program\n";

	std::cin >> n;

	A = new int32_t[n + 1]();

	assert(A != nullptr);

	memset(A, -1, (size_t)(n + 1) * sizeof(*A));
}

int main()
{
	int32_t* arr = nullptr;
	uint32_t value;

	GetInput(arr, value);

	value = CatalanMemoized(value, arr);

	std::cout << "\nNumber of Multiplications are: " << value << std::endl;

	delete[] arr;
	arr = nullptr;

	return 0;
}