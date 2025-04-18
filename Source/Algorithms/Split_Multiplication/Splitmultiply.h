#pragma once

class Splitmultiply
{
public:
    Splitmultiply();
    ~Splitmultiply() = default;

    Splitmultiply(const Splitmultiply& other) = delete;
    Splitmultiply& operator=(const Splitmultiply& other) = delete;

    Splitmultiply(Splitmultiply&& other) = delete;
    Splitmultiply& operator=(Splitmultiply&& other) = delete;

    const uint16_t GetDigits(int64_t x, int64_t y) const;

    const int64_t Calculate(const int64_t x, const int64_t y, const int64_t n) const;

    void GetInput(int64_t& x, int64_t& y) const;
};