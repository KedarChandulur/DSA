#pragma once

class CatalanMemoized
{
public:
    CatalanMemoized();
    ~CatalanMemoized() = default;

    CatalanMemoized(const CatalanMemoized& other) = delete;
    CatalanMemoized& operator=(const CatalanMemoized& other) = delete;

    CatalanMemoized(CatalanMemoized&& other) = delete;
    CatalanMemoized& operator=(CatalanMemoized&& other) = delete;

    void GetInput(int32_t*& A, uint32_t& n) const;

    const uint32_t Calculate(const uint32_t n, int32_t arr[]) const;
};