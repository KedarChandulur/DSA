#pragma once

class SDES_Encrypt
{
public:
    SDES_Encrypt() = delete;
    virtual ~SDES_Encrypt() = default;

    SDES_Encrypt(const bool printProgramStart);

    SDES_Encrypt(const SDES_Encrypt& other) = delete;
    SDES_Encrypt& operator=(const SDES_Encrypt& other) = delete;

    SDES_Encrypt(SDES_Encrypt&& other) = delete;
    SDES_Encrypt& operator=(SDES_Encrypt&& other) = delete;

    void PerformEncryption(uint16_t plaintext, uint16_t key, uint16_t& output) const;
    
    virtual void GetInput(uint16_t& plaintext, uint16_t& key) const;

    void RunDemo() const;

protected:
    void GenerateSubKeys(uint16_t* subkeys, const uint16_t& key) const;
    void PerformRound(uint8_t& lValue, uint8_t& RValue, uint16_t* subkeys, uint16_t& output, uint16_t subkeyNumber) const;

private:
    uint8_t ExpanderFunction(uint8_t& RValue) const;

    void S1Box(uint8_t& l4BitValue) const;
    void S2Box(uint8_t& r4BitValue) const;

    uint16_t PerformEncryptionRoundOperations(uint8_t& lValue, uint8_t& RValue, uint16_t& key) const;
};