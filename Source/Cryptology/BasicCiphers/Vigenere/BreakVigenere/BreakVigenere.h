#pragma once

class BreakVigenere
{
public:
    BreakVigenere();
    ~BreakVigenere() = default;

    BreakVigenere(const BreakVigenere& other) = delete;
    BreakVigenere& operator=(const BreakVigenere& other) = delete;

    BreakVigenere(BreakVigenere&& other) = delete;
    BreakVigenere& operator=(BreakVigenere&& other) = delete;
    
    void GetInput(uint16_t& plaintext, uint16_t& key) const;

    void ReadFile(std::string& cipherTextStringRef) const;

    const size_t GetKeyLength(const char* pa_CipherText) const;

    void GetDisplacement(uint16_t& expectedDisplacementValue, const char* cipherTextString, const uint16_t maxDisplacement, const size_t ciphertextLength) const;

    void GetKeyword(const uint16_t expectedDisplacementValue, const char* cipherTextString, const size_t cipherTextLength);

    void RunDemo();

private:
    uint16_t position;
    std::string result;
};