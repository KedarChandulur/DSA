#include <iostream>
#include <cassert>

#include <string>

//const size_t GetDigits(const int64_t number)
//{
//	return std::to_string(number).length();
//}

const uint16_t GetDigits(int64_t x, int64_t y)
{
	uint16_t xNumDigits = 0;
	uint16_t yNumDigits = 0;

	while (x != 0)
	{
		x /= 10;
	    ++xNumDigits;
	}

	while (y != 0)
	{
		y /= 10;
		++yNumDigits;
	} 

	return (xNumDigits > yNumDigits) ? xNumDigits : yNumDigits;
}

const int64_t SplitMultiply(const int64_t x, const int64_t y, const int64_t n)
{
	if (n == 1)
	{
		return x * y;
	}

	const int64_t m = n / 2;
	
	const int64_t tenPowM = static_cast<int64_t>(std::pow(10, m));
	const int64_t tenPow2M = static_cast<int64_t>(std::pow(10, (2 * m)));

	const int64_t a = (x / tenPowM);
	const int64_t b = (x % tenPowM);

	const int64_t c = (y / tenPowM);
	const int64_t d = (y % tenPowM);

	const int64_t e = SplitMultiply(a, c, m);
	const int64_t f = SplitMultiply(b, d, m);
	const int64_t g = SplitMultiply(b, c, m);
	const int64_t h = SplitMultiply(a, d, m);

	return (tenPow2M * e) + tenPowM * (g + h) + f;
}

int main()
{
	int64_t x = 0;
	int64_t y = 0;

	std::cout << "Enter the integers with a space after each integer.\n";

	scanf_s("%lld %lld", &x, &y);

	const int64_t result = SplitMultiply(x, y, GetDigits(x, y));

	std::cout << "\nProduct of x and y: " << result << "\n";

	return 0;
}