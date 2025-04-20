#include <iostream>

#include "SDESConstants.h"
#include "SDESdecrypt.h"

using namespace SDESConstants;

SDES_Decrypt::SDES_Decrypt(const bool printProgramStart)
	:SDES_Encrypt(false)
{
	if(printProgramStart)
	{
		std::cout << "\nWelcome to Simple DES Decryption Program\n" << std::endl;
	}
}

void SDES_Decrypt::Swap(uint8_t& lValue, uint8_t& rValue) const
{
	uint8_t temp = lValue;
	lValue = rValue;
	rValue = temp;
}

uint16_t SDES_Decrypt::PerformDecryptionRoundOperations(uint8_t& lValue, uint8_t& RValue, uint16_t& key) const
{
	uint16_t output = 0;

	uint16_t subkeys[4];

	SDES_Encrypt::GenerateSubKeys(subkeys, key);

	for (uint16_t i = 4; i > 0; i--)
	{
		SDES_Encrypt::PerformRound(lValue, RValue, subkeys, output, i - 1);
	}

	return output;
}

void SDES_Decrypt::PerformDecryption(uint16_t ciphertext, uint16_t key, uint16_t& output) const
{
	uint8_t lValue = (ciphertext >> 6) & 0x3F;
	uint8_t rValue = (ciphertext) & 0x3F;

	Swap(lValue,rValue);

	output = PerformDecryptionRoundOperations(lValue, rValue, key);

	Swap(lValue,rValue);
	output = lValue;
	output = output << 6;
	output += rValue;
}

void SDES_Decrypt::GetInput(uint16_t& plaintext, uint16_t& key) const
{
	std::cout << "Enter PlainText:" << std::endl;

	std::cin >> plaintext;

	std::cout << "Enter Key:" << std::endl;

	std::cin >> key;
}

void SDES_Decrypt::RunDemo() const
{
	uint16_t plaintext = 0;
	uint16_t key = 0;
	uint16_t ciphertext = 0;
	uint16_t decryptedPlaintext = 0;

	GetInput(plaintext, key);

	SDES_Encrypt::PerformEncryption(plaintext, key, ciphertext);
	std::cout << "\nEncrypted Cipher Text is: " << ciphertext << std::endl;

	PerformDecryption(ciphertext, key, decryptedPlaintext);
	std::cout << "\nDecrypted Plain Text is: " << decryptedPlaintext << std::endl;
}