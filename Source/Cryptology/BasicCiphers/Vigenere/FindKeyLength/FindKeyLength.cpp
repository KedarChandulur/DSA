//FindKeyLength.cpp
#include <iostream>
#include "FindKeyLength.h"
#include "VigenereConstants.h"

using namespace VigenereConstants;

FindKeyLength_Vigenere::FindKeyLength_Vigenere()
{
	std::cout << "\nWelcome to Find Key Length Vigenere Program\n" << std::endl;
}

void FindKeyLength_Vigenere::RunDemo() const
{
	//const char* cipherText = "QHDLXNQLYNGAIGWBCERJFEARNIBKXUSVGZXKYNPXXTKGAATZRQCRFYIDCCLYXHUQXEIXFAFGEAMMALYRGAYXQMTGACDJSYRTLEXUVRVIYFFEGXFKOYSPHGBBYTRESOXUNTXXAKLUAWYDINAAWCZWIFVMCROIUCEIFJYDJAYZJBEOTMUSGAGAYYQNIPTFPYMCBOYDYYSVGWDOJTBZLMFBYJXLQCUDRRIGMIUYWMQUUFRPCZQHTVJOUJSMNRVQQZEJYLACNHRFCPTFENZYEJCLYMBQUCGUMYQDBUAWLQTMOAXCZJBEABHQJYEAMQQDNIRLNTUINRMCYUJAQTZQMGOEXUDEONQPIDBXWNKNIEUNQMBQDUFGXLFXYBVKNTEZCBFJGJUTVHHMBWOZIFQNCTLMBQELYVGNTUHIAXNQUHSROYZJCEFUIACVOBFVAEGBBHGNEIMOHIYRIOZQ";
	//const uint16_t ciphertextLength = 460;
	//const uint16_t maxDisplacement = 14;

	uint16_t maxCoincidenceCount = 0;
	uint16_t expectedDisplacementValue = 0;

	uint16_t coincidenceCount = 0;
	uint16_t displacedIndex = 0;

	printf("Finding Key Length\n\n");

	for (uint32_t displacement = 1; displacement < maxDisplacement; displacement++)
	{
		coincidenceCount = 0;
		for (uint32_t index = 0; index < ciphertextLength; index++)
		{
			displacedIndex = (index + displacement) % ciphertextLength;

			if (cipherText[index] == cipherText[displacedIndex])
				coincidenceCount++;
		}
		
		if (coincidenceCount > maxCoincidenceCount)
		{
			maxCoincidenceCount = coincidenceCount;
			expectedDisplacementValue = displacement;
		}

		printf("Displacement: %u, Coincidence Count: %u\n", displacement, coincidenceCount);
	}

	printf("\nMax Coincidence Count %hu at Displacement %hu\n", maxCoincidenceCount, expectedDisplacementValue);
}