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

struct MyStruct
{
	uint16_t position = 0;
	std::string result = "\0";
};

static MyStruct myStruct;
static const uint16_t maxAlphabet = 26;
static const uint16_t startingAlphabet = 65;
static const double englishFrequencies[maxAlphabet] = { 0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024,
														0.067, 0.075, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001 };

void ReadFile(std::string& cipherTextStringRef)
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
		cipherTextStringRef = "QHDLXNQLYNGAIGWBCERJFEARNIBKXUSVGZXKYNPXXTKGAATZRQCRFYIDCCLYXHUQXEIXFAFGEAMMALYRGAYXQMTGACDJSYRTLEXUVRVIYFFEGXFKOYSPHGBBYTRESOXUNTXXAKLUAWYDINAAWCZWIFVMCROIUCEIFJYDJAYZJBEOTMUSGAGAYYQNIPTFPYMCBOYDYYSVGWDOJTBZLMFBYJXLQCUDRRIGMIUYWMQUUFRPCZQHTVJOUJSMNRVQQZEJYLACNHRFCPTFENZYEJCLYMBQUCGUMYQDBUAWLQTMOAXCZJBEABHQJYEAMQQDNIRLNTUINRMCYUJAQTZQMGOEXUDEONQPIDBXWNKNIEUNQMBQDUFGXLFXYBVKNTEZCBFJGJUTVHHMBWOZIFQNCTLMBQELYVGNTUHIAXNQUHSROYZJCEFUIACVOBFVAEGBBHGNEIMOHIYRIOZQ";
		
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

const size_t GetKeyLength(const char* pa_CipherText)
{
	return strlen(pa_CipherText);
}

void GetDisplacement(uint16_t& expectedDisplacementValue, const char* cipherTextString, const uint16_t maxDisplacement, const size_t ciphertextLength)
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

void GetKeyword(const uint16_t expectedDisplacementValue, const char* cipherTextString, const size_t cipherTextLength)
{
	for (uint16_t displacementIndex = 0; displacementIndex < expectedDisplacementValue; displacementIndex++)
	{
		double frequency_W[maxAlphabet] = { 0.0 };
		uint16_t displacement = displacementIndex;
		uint16_t counter_D = 0;

		while (displacement < cipherTextLength)
		{
			++frequency_W[cipherTextString[displacement] - startingAlphabet];
			displacement += expectedDisplacementValue;
			++counter_D;
		}

		for (uint16_t fIndex = 0; fIndex < maxAlphabet; fIndex++)
		{
			frequency_W[fIndex] = frequency_W[fIndex] / counter_D;
		}

		double dotproductArray[maxAlphabet] = { 0.0 };
		double dotproduct = 0.0;

		for (uint16_t i = 0; i < maxAlphabet; i++)
		{
			for (uint16_t j = 0; j < maxAlphabet; j++)
			{
				dotproduct += frequency_W[(j + i) % maxAlphabet] * englishFrequencies[j];
			}
			dotproductArray[i] = dotproduct;
			dotproduct = 0.0;
		}

		for (uint16_t dIndex = 0; dIndex < maxAlphabet; dIndex++)
		{
			if (dotproduct < dotproductArray[dIndex])
			{
				dotproduct = dotproductArray[dIndex];
				myStruct.position = dIndex;
			}
		}

		char temp = startingAlphabet + myStruct.position;
		myStruct.result += temp;
		myStruct.position = 0;
	}

	printf("Key Length: %hu\n", expectedDisplacementValue);
	printf("Key: %s\n", myStruct.result.c_str());
}

int main()
{
	std::string cipherTextString;

	ReadFile(cipherTextString);

	uint16_t expectedDisplacementValue = 0;
	const uint16_t maxDisplacement = 14;
	const size_t ciphertextLength = GetKeyLength(cipherTextString.c_str());

	GetDisplacement(expectedDisplacementValue, cipherTextString.c_str(), maxDisplacement, ciphertextLength);

	GetKeyword(expectedDisplacementValue, cipherTextString.c_str(), ciphertextLength);

	return 0;
}