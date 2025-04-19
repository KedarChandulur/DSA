#pragma once

class AESEncryptRound
{
public:
    AESEncryptRound();
    ~AESEncryptRound() = default;

    AESEncryptRound(const AESEncryptRound& other) = delete;
    AESEncryptRound& operator=(const AESEncryptRound& other) = delete;

    AESEncryptRound(AESEncryptRound&& other) = delete;
    AESEncryptRound& operator=(AESEncryptRound&& other) = delete;

    void RunDemo() const;

private:
    void PrintFromBuffer(const char* headerText, unsigned char* buffer) const;
    void PerformBitWiseXOR(unsigned char* plaintextBuffer, unsigned char* keyBuffer, unsigned char* resultBuffer) const;
    void PerformSubBytes(unsigned char* resultBuffer) const;
    void PerformShiftRows(unsigned char* resultBuffer) const;
    void PerformMixColumns(unsigned char* resultBuffer) const;
};