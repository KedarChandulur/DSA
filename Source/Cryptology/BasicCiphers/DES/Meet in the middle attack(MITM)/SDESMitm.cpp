#include <iostream>
#include <unordered_map>

#include "SDESConstants.h"
#include "SDESMitm.h"

using namespace SDESConstants;

SDES_MITM::SDES_MITM(const bool printProgramStart)
	:SDES_Decrypt(false)
{
	if(printProgramStart)
	{
		std::cout << "\nWelcome to Simple DES Meet in the Middle Program\n" << std::endl;
	}
}

void SDES_MITM::GetInput(uint16_t& plaintext_1, uint16_t& ciphertext_1, uint16_t& plaintext_2, uint16_t& ciphertext_2) const
{
	std::cout << "Example plain text 1 input : 0\n";
	std::cout << "Enter your input:\n";
	std::cin >> plaintext_1;

	std::cout << "Example cipher text 1 input : 247\n";
	std::cout << "Enter your input:\n";
	std::cin >> ciphertext_1;
	
	std::cout << "Example plain text 2 input : 4095\n";
	std::cout << "Enter your input:\n";
	std::cin >> plaintext_2;
	
	std::cout << "Example cipher text 2 input : 2808\n";
	std::cout << "Enter your input:\n";
	std::cin >> ciphertext_2;
}

void SDES_MITM::Perform_MITM(uint16_t plaintext, uint16_t ciphertext, std::unordered_multimap<uint16_t, uint16_t>& matchingPairs) const
{
	const uint16_t maxValue = 512;
	uint16_t temp = 0;
	std::unordered_map<uint16_t, uint16_t>::const_iterator result;

	uint16_t encryption[maxValue];

	for (uint16_t i = 0; i < maxValue; i++)
	{
		SDES_Encrypt::PerformEncryption(plaintext, i, temp);
		encryption[i] = temp;
	}

	std::unordered_multimap<uint16_t, uint16_t> decryption;
	decryption.reserve(maxValue);

	for (uint16_t i = 0; i < maxValue; i++)
	{
		SDES_Decrypt::PerformDecryption(ciphertext, i, temp);
		decryption.emplace(temp, i);
	}

	for (uint16_t i = 0; i < maxValue; i++)
	{
		temp = encryption[i];
		result = decryption.find(temp);

		while (result != decryption.end())
		{
			matchingPairs.emplace(i, result->second);
			decryption.erase(result);
			result = decryption.find(temp);
		}
	}
}

void SDES_MITM::RunDemo() const
{
	// 0 247 4095 2808

	uint16_t plaintext_1 = 0; // 0
	uint16_t ciphertext_1 = 247; // 247

	uint16_t plaintext_2 = 4095; // 4095
	uint16_t ciphertext_2 = 2808; // 2808

	this->GetInput(plaintext_1, ciphertext_1, plaintext_2, ciphertext_2);

	std::unordered_multimap<uint16_t, uint16_t> matchingPairs_1;
	std::unordered_multimap<uint16_t, uint16_t> matchingPairs_2;

	this->Perform_MITM(plaintext_1, ciphertext_1, matchingPairs_1);
	this->Perform_MITM(plaintext_2, ciphertext_2, matchingPairs_2);

	std::unordered_multimap<uint16_t, uint16_t>::const_iterator result;
	std::unordered_multimap<uint16_t, uint16_t> matchingPairs;

	for (auto iteration = matchingPairs_1.begin(); iteration != matchingPairs_1.end(); iteration++)
	{
		result = matchingPairs_2.find(iteration->first);
		while (result != matchingPairs_2.end())
		{
			if (iteration->second != result->second)
			{
				matchingPairs_2.erase(result);
				result = matchingPairs_2.find(iteration->first);
			}
			else
			{
				matchingPairs.emplace(iteration->first, result->second);
				break;
			}
		}
	}

	if (matchingPairs.size() < 1)
	{
		std::cout << "\nNo matching pair of keys found. \n";
	}
	else
	{
		std::cout << "\nKeys Found: \n";

		for (auto iteration = matchingPairs.begin(); iteration != matchingPairs.end(); iteration++)
		{
			std::cout << "Key 1: " << iteration->first << "\t";
			std::cout << "Key 2: " << iteration->second << "\n";
		}
	}
}