#pragma once

#include <unordered_map>
#include "SDESdecrypt.h"

class SDES_MITM : public SDES_Decrypt
{
public:
    SDES_MITM() = delete;
    ~SDES_MITM() = default;

    SDES_MITM(const bool printProgramStart);

    SDES_MITM(const SDES_MITM& other) = delete;
    SDES_MITM& operator=(const SDES_MITM& other) = delete;

    SDES_MITM(SDES_MITM&& other) = delete;
    SDES_MITM& operator=(SDES_MITM&& other) = delete;

    void GetInput(uint16_t& plaintext_1, uint16_t& ciphertext_1, uint16_t& plaintext_2, uint16_t& ciphertext_2) const;

    void Perform_MITM(uint16_t plaintext, uint16_t ciphertext, std::unordered_multimap<uint16_t, uint16_t>& matchingPairs) const;

    void RunDemo() const;
};