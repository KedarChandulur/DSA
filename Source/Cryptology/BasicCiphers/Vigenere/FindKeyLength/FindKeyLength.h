#pragma once

class FindKeyLength_Vigenere
{
public:
    FindKeyLength_Vigenere();
    ~FindKeyLength_Vigenere() = default;

    FindKeyLength_Vigenere(const FindKeyLength_Vigenere& other) = delete;
    FindKeyLength_Vigenere& operator=(const FindKeyLength_Vigenere& other) = delete;

    FindKeyLength_Vigenere(FindKeyLength_Vigenere&& other) = delete;
    FindKeyLength_Vigenere& operator=(FindKeyLength_Vigenere&& other) = delete;
    
    void GetInput(uint16_t& plaintext, uint16_t& key) const;

    void RunDemo() const;
};