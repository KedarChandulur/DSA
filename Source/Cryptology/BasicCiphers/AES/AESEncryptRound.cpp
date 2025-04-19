#include <iostream>
#include <__msvc_int128.hpp>

#include "AESConstants.h"
#include "AESEncryptRound.h"

using namespace AESConstants;

AESEncryptRound::AESEncryptRound()
{
	std::cout << "\nWelcome to AES Encrypt Round Program\n" << std::endl;
}

void AESEncryptRound::PrintFromBuffer(const char* headerText, unsigned char* buffer) const
{
    std::cout << headerText;

    int value = 0;
    for (int i = 0; i < columnSize; i++)
    {
        value = (int)buffer[i];

        if (value < 10)
            std::cout << "0";

        std::cout << std::hex << (int)buffer[i] << " ";

        value = (int)buffer[i + 4];

        if (value < 10)
            std::cout << "0";

        std::cout << std::hex << (int)buffer[i + 4] << " ";

        value = (int)buffer[i + 8];

        if (value < 10)
            std::cout << "0";

        std::cout << std::hex << (int)buffer[i + 8] << " ";

        value = (int)buffer[i + 12];

        if (value < 10)
            std::cout << "0";

        std::cout << std::hex << (int)buffer[i + 12] << " ";

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void AESEncryptRound::PerformBitWiseXOR(unsigned char* plaintextBuffer, unsigned char* keyBuffer, unsigned char* resultBuffer) const
{
    for (int i = 0; i < buffersize; i++)
    {
        resultBuffer[i] = plaintextBuffer[i] ^ keyBuffer[i];
    }

    PrintFromBuffer("After ARK with original key\n", resultBuffer);
}

void AESEncryptRound::PerformSubBytes(unsigned char* resultBuffer) const
{
    for (int i = 0; i < buffersize; i++) 
    {
        resultBuffer[i] = ByteSub[resultBuffer[i]];
    }

    PrintFromBuffer("After SB\n", resultBuffer);
}

void AESEncryptRound::PerformShiftRows(unsigned char* resultBuffer) const
{
    unsigned char tmp = resultBuffer[1];
    resultBuffer[1] = resultBuffer[5];
    resultBuffer[5] = resultBuffer[9];
    resultBuffer[9] = resultBuffer[13];
    resultBuffer[13] = tmp;

    tmp = resultBuffer[2];
    resultBuffer[2] = resultBuffer[10];
    resultBuffer[10] = tmp;
    tmp = resultBuffer[6];
    resultBuffer[6] = resultBuffer[14];
    resultBuffer[14] = tmp;

    tmp = resultBuffer[15];
    resultBuffer[15] = resultBuffer[11];
    resultBuffer[11] = resultBuffer[7];
    resultBuffer[7] = resultBuffer[3];
    resultBuffer[3] = tmp;

    PrintFromBuffer("After SR\n", resultBuffer);
}

void AESEncryptRound::PerformMixColumns(unsigned char* resultBuffer) const
{
    unsigned char tmp[buffersize];
    for (int i = 0; i < columnSize; i++) {
        tmp[columnSize * i] = GF2_Buffer[resultBuffer[columnSize * i]] ^ GF3_Buffer[resultBuffer[columnSize * i + 1]] ^ resultBuffer[columnSize * i + 2] ^ resultBuffer[columnSize * i + 3];
        tmp[columnSize * i + 1] = resultBuffer[columnSize * i] ^ GF2_Buffer[resultBuffer[columnSize * i + 1]] ^ GF3_Buffer[resultBuffer[columnSize * i + 2]] ^ resultBuffer[columnSize * i + 3];
        tmp[columnSize * i + 2] = resultBuffer[columnSize * i] ^ resultBuffer[columnSize * i + 1] ^ GF2_Buffer[resultBuffer[columnSize * i + 2]] ^ GF3_Buffer[resultBuffer[columnSize * i + 3]];
        tmp[columnSize * i + 3] = GF3_Buffer[resultBuffer[columnSize * i]] ^ resultBuffer[columnSize * i + 1] ^ resultBuffer[columnSize * i + 2] ^ GF2_Buffer[resultBuffer[columnSize * i + 3]];
    }

    for (int i = 0; i < buffersize; i++) {
        resultBuffer[i] = tmp[i];
    }

    PrintFromBuffer("After MC\n", resultBuffer);
}

void AESEncryptRound::RunDemo() const
{
    std::cout << "Encryption/Decrypt is based on AES-128" << std::endl;
    
    std::cout << "Prints from top to bottom first and then goes to right" << std::endl;

    std::cout << "Prints in hex without 0x\n" << std::endl;

    this->PrintFromBuffer("Original plaintext\n", plaintextBuffer);
    //this->PrintFromBuffer("My Key text value: ", keyBuffer);

    this->PerformBitWiseXOR(plaintextBuffer, keyBuffer, resultBuffer);

    this->PerformSubBytes(resultBuffer);
    this->PerformShiftRows(resultBuffer);
    this->PerformMixColumns(resultBuffer);
}