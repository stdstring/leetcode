#include <algorithm>
#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minIncrementForUnique(std::vector<int> const &nums) const
    {
        const auto [minElement, maxElement] = std::minmax_element(nums.cbegin(), nums.cend());
        const int minNumber = *minElement;
        const int maxNumber = *maxElement;
        std::vector<size_t> countData(1LL + maxNumber - minNumber);
        for (const int number : nums)
            ++countData[0LL + number - minNumber];
        size_t incrementCount = 0;
        size_t prevCount = countData.front() - 1;
        for (size_t index = 1; index < countData.size(); ++index)
        {
            incrementCount += prevCount;
            if (countData[index] == 0 && prevCount > 0)
                --prevCount;
            if (countData[index] > 0)
                prevCount += (countData[index] - 1);
        }
        return static_cast<int>(incrementCount + calcIncrementCount(prevCount));
    }

private:
    [[nodiscard]] size_t calcIncrementCount(size_t portion) const
    {
        return (1 + portion) * portion / 2;
    }
};

}

namespace MinIncrementToMakeArrayUniqueTask
{

TEST(MinIncrementToMakeArrayUniqueTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minIncrementForUnique({1, 2, 2}));
    ASSERT_EQ(6, solution.minIncrementForUnique({3, 2, 1, 2, 1, 7}));
}

}