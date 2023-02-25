#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int differenceOfSum(std::vector<int> const &nums) const
    {
        return std::accumulate(nums.cbegin(), nums.cend(), 0, [this](int acc, int current){ return acc + current - calcDigitSum(current); });
    }

private:
    [[nodiscard]] int calcDigitSum(int number) const
    {
        int result = 0;
        while (number > 0)
        {
            result += (number % 10);
            number /= 10;
        }
        return result;
    }
};

}

namespace DiffBetweenElementDigitSumOfArrayTask
{

TEST(DiffBetweenElementDigitSumOfArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.differenceOfSum({1, 15, 6, 3}));
    ASSERT_EQ(0, solution.differenceOfSum({1, 2, 3, 4}));
}

}