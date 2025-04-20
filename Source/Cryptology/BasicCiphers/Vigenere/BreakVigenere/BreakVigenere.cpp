//BreakVigenere.cpp

//Remove any spaces from your text file.

//If you see -> Error: Unable to open file, follow the steps below,
//To get the vigenereciphertext.txt file correctly open and to be read,
//Please keep the vigenereciphertext.txt file in the solution directory,
//if that doesn't work move the file to project directory,
//if that doesn't work then move the file to the place where the executable(.exe) is present,
//(.exe) should be there in either Debug or Release folder depending on the solution configuration you are running on.

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "BreakVigenere.h"
#include "VigenereConstants.h"

using namespace VigenereConstants;

BreakVigenere::BreakVigenere()
	: position(0), result("\0")
{
	std::cout << "\nWelcome to Break Vigenere Program\n" << std::endl;
}

void BreakVigenere::ReadFile(std::string& cipherTextStringRef) const
{
	std::ifstream myfile("vigenereciphertext.txt");

	if (myfile.is_open())
	{
		std::string temp = cipherTextStringRef = "\0";
		while (getline(myfile, temp))
		{
			if(temp != "\0" && temp != "" && temp != " ")
				cipherTextStringRef += temp;
		}
		myfile.close();
	}
	else
	{
		//File not found setting default value.
		cipherTextStringRef = cipherText;
		
		//printf("Error: Unable to open file :(\n");
		//printf("To get the vigenereciphertext.txt file correctly open and to be read,\n");
		//printf("Please keep the vigenereciphertext.txt file in the solution directory,\n");
		//printf("if that doesn't work move the file to project directory,\n");
		//printf("if that doesn't work then move the file to the place where the executable(.exe) is present,\n");
		//printf("(.exe) should be there in either Debug or Release folder depending on the solution configuration you are running on.\n\n");
		//printf("Since the program failed to run applying default cipher text to the input value.\n");
		//printf("Default cipher text: %s\n\n", cipherTextStringRef.c_str());
	}
}

const size_t BreakVigenere::GetKeyLength(const char* pa_CipherText) const
{
	return strlen(pa_CipherText);
}

void BreakVigenere::GetDisplacement(uint16_t& expectedDisplacementValue, const char* cipherTextString, const uint16_t maxDisplacement, const size_t ciphertextLength) const
{
	uint16_t maxCoincidenceCount = 0;
	uint16_t coincidenceCount = 0;
	uint16_t displacedIndex = 0;

	for (uint32_t displacement = 1; displacement < maxDisplacement; displacement++)
	{
		coincidenceCount = 0;
		for (uint32_t index = 0; index < ciphertextLength; index++)
		{
			displacedIndex = static_cast<uint16_t>((static_cast<size_t>(index) + static_cast<size_t>(displacement)) % ciphertextLength);

			if (cipherTextString[index] == cipherTextString[displacedIndex])
				coincidenceCount++;
		}

		if (coincidenceCount > maxCoincidenceCount)
		{
			maxCoincidenceCount = coincidenceCount;
			expectedDisplacementValue = displacement;
		}
	}
}

void BreakVigenere::GetKeyword(const uint16_t expectedDisplacementValue, const char* cipherTextString, const size_t cipherTextLength)
{
	for (uint16_t displacementIndex = 0; displacementIndex < expectedDisplacementValue; displacementIndex++)
	{
		double frequency_W[maxAlphabets] = { 0.0 };
		uint16_t displacement = displacementIndex;
		uint16_t counter_D = 0;

		while (displacement < cipherTextLength)
		{
			++frequency_W[cipherTextString[displacement] - startingAlphabetIndex];
			displacement += expectedDisplacementValue;
			++counter_D;
		}

		for (uint16_t fIndex = 0; fIndex < maxAlphabets; fIndex++)
		{
			frequency_W[fIndex] = frequency_W[fIndex] / counter_D;
		}

		double dotproductArray[maxAlphabets] = { 0.0 };
		double dotproduct = 0.0;

		for (uint16_t i = 0; i < maxAlphabets; i++)
		{
			for (uint16_t j = 0; j < maxAlphabets; j++)
			{
				dotproduct += frequency_W[(j + i) % maxAlphabets] * englishFrequencies[j];
			}
			dotproductArray[i] = dotproduct;
			dotproduct = 0.0;
		}

		for (uint16_t dIndex = 0; dIndex < maxAlphabets; dIndex++)
		{
			if (dotproduct < dotproductArray[dIndex])
			{
				dotproduct = dotproductArray[dIndex];
				this->position = dIndex;
			}
		}

		char temp = startingAlphabetIndex + this->position;
		this->result += temp;
		this->position = 0;
	}

	printf("Key Length: %hu\n", expectedDisplacementValue);
	printf("Key: %s\n", this->result.c_str());
}

void BreakVigenere::RunDemo()
{
	std::string cipherTextString;

	ReadFile(cipherTextString);

	uint16_t expectedDisplacementValue = 0;
	const uint16_t maxDisplacement = 14;
	const size_t ciphertextLength = GetKeyLength(cipherTextString.c_str());

	GetDisplacement(expectedDisplacementValue, cipherTextString.c_str(), maxDisplacement, ciphertextLength);

	GetKeyword(expectedDisplacementValue, cipherTextString.c_str(), ciphertextLength);
}