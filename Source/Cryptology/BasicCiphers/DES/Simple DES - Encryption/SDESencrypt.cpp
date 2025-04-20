#include <iostream>

#include "SDESConstants.h"
#include "SDESencrypt.h"

using namespace SDESConstants;

SDES_Encrypt::SDES_Encrypt(const bool printProgramStart)
{
	if(printProgramStart)
	{
		std::cout << "\nWelcome to Simple DES Encryption Program\n" << std::endl;
	}
}

uint8_t SDES_Encrypt::ExpanderFunction(uint8_t& RValue) const
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

void SDES_Encrypt::S1Box(uint8_t& l4BitValue) const
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

void SDES_Encrypt::S2Box(uint8_t& r4BitValue) const
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

void SDES_Encrypt::GenerateSubKeys(uint16_t* subkeys, const uint16_t& key) const
{
	subkeys[0] = (key & 0b111111110) >> 1;
	subkeys[1] = ((key & 0b011111111) << 0) + ((key & 0b000000000) >> 9);
	subkeys[2] = ((key & 0b001111111) << 1) + ((key & 0b100000000) >> 8);
	subkeys[3] = ((key & 0b000111111) << 2) + ((key & 0b110000000) >> 7);
}

void SDES_Encrypt::PerformRound(uint8_t& lValue, uint8_t& RValue, uint16_t* subkeys, uint16_t& output, uint16_t subkeyNumber) const
{
	uint8_t r8BitValue = ExpanderFunction(RValue);

	uint16_t refinedKey = subkeys[subkeyNumber];

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

uint16_t SDES_Encrypt::PerformEncryptionRoundOperations(uint8_t& lValue, uint8_t& RValue, uint16_t& key) const
{
	uint16_t output = 0;

	uint16_t subkeys[4];

	GenerateSubKeys(subkeys, key);

	for (uint16_t i = 0; i < 4; i++)
	{
		PerformRound(lValue, RValue, subkeys, output, i);
	}

	return output;
}

void SDES_Encrypt::PerformEncryption(uint16_t plaintext, uint16_t key, uint16_t& output) const
{
	uint8_t lValue = (plaintext >> 6) & 0x3F;
	uint8_t rValue = (plaintext) & 0x3F;
	output = PerformEncryptionRoundOperations(lValue, rValue, key);
}

void SDES_Encrypt::GetInput(uint16_t& plaintext, uint16_t& key) const
{
	std::cout << "Enter PlainText:" << std::endl;

	std::cin >> plaintext;

	std::cout << "Enter Key:" << std::endl;

	std::cin >> key;
}

void SDES_Encrypt::RunDemo() const
{
	uint16_t plaintext = 0;
	uint16_t key = 0;
	uint16_t output;

	GetInput(plaintext, key);

	PerformEncryption(plaintext, key, output);

	std::cout << "\nCipher Text is: " << (int)output << std::endl;
}