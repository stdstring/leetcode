#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSumDivThree(std::vector<int> const &nums) const
    {
        constexpr int modCount = 3;
        std::vector<int> prevDp(modCount, 0);
        std::vector<int> currentDp(modCount, 0);
        for (int number : nums)
        {
            for (int modValue = 0; modValue < modCount; ++modValue)
                currentDp[modValue] = prevDp[modValue];
            for (int modValue = 0; modValue < modCount; ++modValue)
            {
                if ((modValue > 0) && (prevDp[modValue] == 0))
                    continue;
                const int currentMod = (number + modValue) % 3;
                currentDp[currentMod] = std::max(currentDp[currentMod], prevDp[modValue] + number);
            }
            std::swap(prevDp, currentDp);
        }
        return prevDp[0];
    }
};

}

namespace GreatestSumDivisibleBy3Task
{

TEST(GreatestSumDivisibleBy3TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(18, solution.maxSumDivThree({3, 6, 5, 1, 8}));
    ASSERT_EQ(0, solution.maxSumDivThree({4}));
    ASSERT_EQ(12, solution.maxSumDivThree({1, 2, 3, 4, 4}));
}

TEST(GreatestSumDivisibleBy3TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.maxSumDivThree({2, 6, 2, 2, 7}));
}

}