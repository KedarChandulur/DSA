#pragma once

class BasicNumbersSort
{
public:
    BasicNumbersSort();
    ~BasicNumbersSort() = default;

    BasicNumbersSort(const BasicNumbersSort& other) = delete;
    BasicNumbersSort& operator=(const BasicNumbersSort& other) = delete;

    BasicNumbersSort(BasicNumbersSort&& other) = delete;
    BasicNumbersSort& operator=(BasicNumbersSort&& other) = delete;

    void QuickSort(int32_t A[], const int32_t n) const;

    void GetInput(int32_t*& A, int32_t& n) const;

private:
    void Swap(int32_t* first, int32_t* last) const;

    const int32_t Partition(int32_t A[], const int32_t startingIndex, const int32_t n, const int32_t p) const;

    void internalQuickSort(int32_t A[], const int32_t startingIndex, const int32_t n) const;
};