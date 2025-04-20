#pragma once

// Recurrence relation is:
// if i = 0 || j = 0      ---> 0
// else                   ---> max(E[i][j - 1], E[i - 1][j], E[i - 1][j - 1]) + E[i][j]

class MaxProfit
{
public:
    MaxProfit();
    ~MaxProfit() = default;

    MaxProfit(const MaxProfit& other) = delete;
    MaxProfit& operator=(const MaxProfit& other) = delete;

    MaxProfit(MaxProfit&& other) = delete;
    MaxProfit& operator=(MaxProfit&& other) = delete;

    const bool GetInput(std::vector<std::vector<uint32_t>>& arr);

    const uint32_t Calculate(const std::vector<std::vector<uint32_t>>& arr) const;

    void PrintMatrix(const std::vector<std::vector<uint32_t>>& arr, const char* message, uint32_t rows = 0, uint32_t cols = 0) const;

    void RunDemo();

private:
    uint32_t m_rows;
    uint32_t m_cols;
};