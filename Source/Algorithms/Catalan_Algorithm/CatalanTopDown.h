#pragma once

class CatalanTopDown
{
public:
    CatalanTopDown();
    ~CatalanTopDown() = default;

    CatalanTopDown(const CatalanTopDown& other) = delete;
    CatalanTopDown& operator=(const CatalanTopDown& other) = delete;

    CatalanTopDown(CatalanTopDown&& other) = delete;
    CatalanTopDown& operator=(CatalanTopDown&& other) = delete;

    void GetInput(uint32_t& n) const;
    const uint32_t GetInput() const;

    const uint32_t Calculate(const uint32_t n) const;
};