#pragma once

class MinNoOfBills
{
public:
    MinNoOfBills();
    ~MinNoOfBills() = default;

    MinNoOfBills(const MinNoOfBills& other) = delete;
    MinNoOfBills& operator=(const MinNoOfBills& other) = delete;

    MinNoOfBills(MinNoOfBills&& other) = delete;
    MinNoOfBills& operator=(MinNoOfBills&& other) = delete;
    
    const std::vector<int> FindMinDenomination(const int target, const std::vector<int>& denominations) const;

    const bool GetInput(std::vector<int>& denominations, int& target) const;

    void RunDemo() const;

    bool ValidateSolution(const int target, const std::vector<int>& solution) const;

private:
    void internalFindMinDenomination(const int target, const std::vector<int>& denominations, std::vector<int>& solution) const;
};