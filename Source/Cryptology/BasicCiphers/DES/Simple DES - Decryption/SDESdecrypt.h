#pragma once
#include "SDESencrypt.h"

class SDES_Decrypt : public SDES_Encrypt
{
public:
    SDES_Decrypt() = delete;
    virtual ~SDES_Decrypt() = default;

    SDES_Decrypt(const bool printProgramStart);

    SDES_Decrypt(const SDES_Decrypt& other) = delete;
    SDES_Decrypt& operator=(const SDES_Decrypt& other) = delete;

    SDES_Decrypt(SDES_Decrypt&& other) = delete;
    SDES_Decrypt& operator=(SDES_Decrypt&& other) = delete;

    void PerformDecryption(uint16_t ciphertext, uint16_t key, uint16_t& output) const;

    virtual void GetInput(uint16_t& plaintext, uint16_t& key) const final;

    void RunDemo() const;

private:
    uint16_t PerformDecryptionRoundOperations(uint8_t& lValue, uint8_t& RValue, uint16_t& key) const;

    void Swap(uint8_t& lValue, uint8_t& rValue) const;
};