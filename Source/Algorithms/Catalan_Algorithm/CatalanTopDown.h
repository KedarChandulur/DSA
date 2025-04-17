#pragma once

class CatalanTopDown
{
public:
    CatalanTopDown() = default;
    ~CatalanTopDown() = default;

    CatalanTopDown(const CatalanTopDown& other) = default;
    CatalanTopDown& operator=(const CatalanTopDown& other) = default;

    CatalanTopDown(CatalanTopDown&& other) = default;
    CatalanTopDown& operator=(CatalanTopDown&& other) = default;

    void GetInput(uint32_t& n) const;
    const uint32_t GetInput() const;

    const uint32_t Calculate(const uint32_t n) const;
};