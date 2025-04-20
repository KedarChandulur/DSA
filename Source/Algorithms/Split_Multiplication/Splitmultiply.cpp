#include <iostream>
#include <cassert>

#include <string>

#include "Splitmultiply.h"

Splitmultiply::Splitmultiply()
{
	std::cout << "\nWelcome to Split Multiply Program\n" << std::endl;
}

//const size_t GetDigits(const int64_t number)
//{
//	return std::to_string(number).length();
//}

const uint16_t Splitmultiply::GetDigits(int64_t x, int64_t y) const
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

const int64_t Splitmultiply::Calculate(const int64_t x, const int64_t y, const int64_t n) const
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

	const int64_t e = Calculate(a, c, m);
	const int64_t f = Calculate(b, d, m);
	const int64_t g = Calculate(b, c, m);
	const int64_t h = Calculate(a, d, m);

	return (tenPow2M * e) + tenPowM * (g + h) + f;
}

void Splitmultiply::GetInput(int64_t& x, int64_t& y) const
{
	std::cout << "Example Input: \n";
	std::cout << "222223 642522\n";

	std::cout << "Enter the integers with a space after each integer.\n";
    
	scanf_s("%lld %lld", &x, &y);
}

void Splitmultiply::RunDemo() const
{
	int64_t x = 0;
	int64_t y = 0;

	this->GetInput(x, y);

	const int64_t result = this->Calculate(x, y, this->GetDigits(x, y));

	std::cout << "\nProduct of x and y: " << result << "\n";
}