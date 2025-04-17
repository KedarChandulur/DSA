#include <iostream>
#include <cassert>

void Swap(int32_t* first, int32_t* last)
{
	int32_t temp = *first;
    *first = *last;
    *last = temp;
}

const int32_t Partition(int32_t A[], const int32_t startingIndex, const int32_t n, const int32_t p)
{
	Swap(&A[p], &A[n]);

	int32_t l = startingIndex - 1;

	for (int32_t i = startingIndex; i < n; ++i)
	{
		if (A[i] < A[n])
		{
			l = l + 1;
			Swap(&A[l], &A[i]);
		}
	}

	Swap(&A[n], &A[l + 1]);

	return l + 1;
}

void internalQuickSort(int32_t A[], const int32_t startingIndex, const int32_t n)
{
	if (n > 1 && startingIndex < n)
	{
		const int32_t p = rand() % (n - startingIndex + 1) + startingIndex;
		const int32_t r = Partition(A, startingIndex, n, p);

		internalQuickSort(A, startingIndex, r - 1);
		internalQuickSort(A, r + 1, n);
	}
}

void QuickSort(int32_t A[], const int32_t n)
{
	internalQuickSort(A, 0, n - 1);
}

void GetInput(int32_t*& A, int32_t& n)
{
	int32_t* ATemp = A;
	int32_t input = 0;

	while (std::cin.peek() != '\n')
	{
		if (std::cin >> input)
		{
			if (n < 1)
			{
				ATemp = new int32_t[input]();
				A = ATemp;
				n = input;

				assert(n > 0);
				assert(A != nullptr);
				continue;
			}

			*ATemp++ = input;
		}
	}
}

int main()
{
	srand((uint32_t)time(NULL));

	std::cout << "Enter the size of array, followed by the integers with a space after each integer.\n";

	// Example input: 7 56 28 14 22 42 43 54
	int32_t* A = nullptr;
	int32_t n = 0;

	GetInput(A, n);

	printf("\nInput:\n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", A[i]);
	}

	printf("\n");

	assert(A != nullptr);
	
	QuickSort(A, n);

	printf("\nOutput:\n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", A[i]);
	}

	printf("\n");

	delete[] A;
	A = nullptr;

	return 0;
}