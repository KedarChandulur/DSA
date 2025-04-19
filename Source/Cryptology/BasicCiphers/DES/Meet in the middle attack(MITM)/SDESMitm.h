#pragma once

#include <unordered_map>

class SDES_MITM
{
public:
    SDES_MITM();
    ~SDES_MITM() = default;

    SDES_MITM(const SDES_MITM& other) = delete;
    SDES_MITM& operator=(const SDES_MITM& other) = delete;

    SDES_MITM(SDES_MITM&& other) = delete;
    SDES_MITM& operator=(SDES_MITM&& other) = delete;

    void GetInput(uint16_t& plaintext_1, uint16_t& ciphertext_1, uint16_t& plaintext_2, uint16_t& ciphertext_2) const;

    void Encrypt(uint16_t plaintext, uint16_t key, uint16_t& output) const;
    void Decrypt(uint16_t ciphertext, uint16_t key, uint16_t& output) const;

    void Perform_MITM(uint16_t plaintext, uint16_t ciphertext, std::unordered_multimap<uint16_t, uint16_t>& matchingPairs) const;

    void RunDemo() const;

private:
    void Swap(uint8_t& lValue, uint8_t& rValue) const;
    uint8_t ExpanderFunction(uint8_t& RValue) const;

    void S1Box(uint8_t& l4BitValue) const;
    void S2Box(uint8_t& r4BitValue) const;

    void GenerateSubKeys(uint16_t* subkeys, const uint16_t& key) const;
    void PerformRound(uint8_t& lValue, uint8_t& RValue, uint16_t* subkeys, uint16_t& output, uint16_t subkeyNumber) const;

    uint16_t PerformEncryptionRoundOperations(uint8_t& lValue, uint8_t& RValue, uint16_t& key) const;
    uint16_t PerformDecryptionRoundOperations(uint8_t& lValue, uint8_t& RValue, uint16_t& key) const;
};