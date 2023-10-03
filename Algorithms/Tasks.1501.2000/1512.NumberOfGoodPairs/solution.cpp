#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numIdenticalPairs(std::vector<int> const &nums) const
    {
        std::unordered_map<int, int> numberMap;
        for (int number : nums)
            ++numberMap[number];
        int result = 0;
        for (const auto &[_, count] : numberMap)
            result += calcArithProgressionSum(count - 1);
        return result;
    }

private:
    [[nodiscard]] int calcArithProgressionSum(int n) const
    {
        return (1 + n) * n / 2;
    }
};

}

namespace NumberOfGoodPairsTask
{

TEST(NumberOfGoodPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.numIdenticalPairs({1, 2, 3, 1, 1, 3}));
    ASSERT_EQ(6, solution.numIdenticalPairs({1, 1, 1, 1}));
    ASSERT_EQ(0, solution.numIdenticalPairs({1, 2, 3}));
}

}