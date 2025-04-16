#include <iostream>

static uint16_t s1BoxArray1[] = { 0b101, 0b010, 0b001, 0b110, 0b011, 0b100, 0b111, 0b000 };
static uint16_t s1BoxArray2[] = { 0b001, 0b100, 0b110, 0b010, 0b000, 0b111, 0b101, 0b011 };
static uint16_t s2BoxArray1[] = { 0b100, 0b000, 0b110, 0b101, 0b111, 0b001, 0b011, 0b010 };
static uint16_t s2BoxArray2[] = { 0b101, 0b011, 0b000, 0b111, 0b110, 0b010, 0b001, 0b100 };

uint8_t ExpanderFunction(uint8_t& RValue)
{
	char bit1 = (RValue & 0b100000) >> 5;
	char bit2 = (RValue & 0b010000) >> 4;
	char bit3 = (RValue & 0b001000) >> 3;
	char bit4 = (RValue & 0b000100) >> 2;
	char bit5 = (RValue & 0b000010) >> 1;
	char bit6 = (RValue & 0b000001) >> 0;

	uint8_t expandedR = (bit1 << 7) + (bit2 << 6) + (bit4 << 5) + (bit3 << 4) + (bit4 << 3) + (bit3 << 2) + (bit5 << 1) + (bit6 << 0);

	return expandedR;
}

void S1Box(uint8_t& l4BitValue)
{
	uint8_t fourBitValue = l4BitValue & 0b1111;

	uint8_t l4Row = fourBitValue >> 3;

	uint8_t column = fourBitValue & 0b111;

	if (l4Row == 0)
	{
		l4BitValue = static_cast<uint8_t>(s1BoxArray1[column]);
	}
	else if(l4Row == 1)
	{
		l4BitValue = static_cast<uint8_t>(s1BoxArray2[column]);
	}
}

void S2Box(uint8_t& r4BitValue)
{
	uint8_t fourBitValue = r4BitValue & 0b1111;

	uint8_t r4Row = fourBitValue >> 3;

	uint8_t column = fourBitValue & 0b111;

	if (r4Row == 0)
	{
		r4BitValue = static_cast<uint8_t>(s2BoxArray1[column]);
	}
	else if (r4Row == 1)
	{
		r4BitValue = static_cast<uint8_t>(s2BoxArray2[column]);
	}
}

uint16_t PerformRoundOperations(uint8_t& lValue, uint8_t& RValue, uint16_t& key)
{
	uint16_t output = 0;
	for (uint16_t i = 0; i < 4; i++)
	{
		uint8_t r8BitValue = ExpanderFunction(RValue);

		uint16_t refinedKey = 0;
		if (i == 0)
		{
			refinedKey = (key & 0b111111110) >> 1;
		}
		if (i == 1)
		{
			refinedKey = ((key & 0b011111111) << 0) + ((key & 0b000000000) >> 9);
		}
		if (i == 2)
		{
			refinedKey = ((key & 0b001111111) << 1) + ((key & 0b100000000) >> 8);
		}
		if (i == 3)
		{
			refinedKey = ((key & 0b000111111) << 2) + ((key & 0b110000000) >> 7);
		}

		r8BitValue ^= refinedKey;

		uint8_t l4BitValue = (r8BitValue & 0b11110000) >> 4;
		uint8_t r4BitValue = (r8BitValue & 0b1111) >> 0;

		S1Box(l4BitValue);
		S2Box(r4BitValue);

		l4BitValue = l4BitValue << 3;

		uint8_t out = 0;
		out = lValue ^ (l4BitValue + r4BitValue);
		
		lValue = RValue;
		RValue = out;

		output = lValue;
		output = output << 6;
		output += RValue;
	}

	return output;
}

void Encrypt(uint16_t plaintext, uint16_t key)
{
	uint8_t lValue = (plaintext >> 6) & 0x3F;
	uint8_t rValue = (plaintext) & 0x3F;

	uint16_t output = PerformRoundOperations(lValue, rValue, key);

	std::cout << "\nCipher Text is: " << (int)output << std::endl;
}

int main()
{
	uint16_t plaintext = 0;
	uint16_t key = 0;

	std::cout << "Encryption using SDES\n" << std::endl;

	std::cout << "Enter PlainText:" << std::endl;

	std::cin >> plaintext;

	std::cout << "Enter Key:" << std::endl;

	std::cin >> key;

	Encrypt(plaintext, key);

	return 0;
}