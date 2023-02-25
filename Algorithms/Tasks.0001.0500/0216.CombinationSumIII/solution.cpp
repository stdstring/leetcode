#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum3(int k, int n) const
    {
        std::vector<std::vector<int>> dest;
        std::vector<int> combination;
        generateCombinations(dest, combination, 1, 0, k, n);
        return dest;
    }

private:
    void generateCombinations(std::vector<std::vector<int>> &dest, std::vector<int> &combination, size_t currentNumber, size_t currentSum, size_t k, size_t n) const
    {
        if (combination.size() == k)
        {
            if (currentSum == n)
                dest.push_back(combination);
            return;
        }
        if (currentNumber + currentSum > n)
            return;
        for (size_t number = currentNumber; number <= 10 - (k - combination.size()); ++number)
        {
            combination.push_back(static_cast<int>(number));
            generateCombinations(dest, combination, number + 1, number + currentSum, k, n);
            combination.pop_back();
        }
    }
};

}

namespace CombinationSumIIITask
{

TEST(CombinationSumIIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 4}}), solution.combinationSum3(3, 7));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 6}, {1, 3, 5}, {2, 3, 4}}), solution.combinationSum3(3, 9));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.combinationSum3(4, 1));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.combinationSum3(3, 2));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 3, 4, 5, 6, 7, 8, 9}}), solution.combinationSum3(9, 45));
}

}