#include <algorithm>
#include <climits>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findLHS(std::vector<int> const &nums) const
    {
        std::map<int, size_t> numbers;
        for (int number : nums)
            ++numbers[number];
        int prevNumber = INT_MIN;
        size_t prevCount = 0;
        size_t bestCount = 0;
        for (auto const &entry : numbers)
        {
            const int currentNumber = entry.first;
            const size_t currentCount = entry.second;
            if (currentNumber == prevNumber + 1)
                bestCount = std::max(bestCount, prevCount + currentCount);
            prevNumber = currentNumber;
            prevCount = currentCount;
        }
        return static_cast<int>(bestCount);
    }
};

}

namespace LongestHarmoniousSubsequenceTask
{

TEST(LongestHarmoniousSubsequenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.findLHS({1, 3, 2, 2, 5, 2, 3, 7}));
    ASSERT_EQ(2, solution.findLHS({1, 2, 3, 4}));
    ASSERT_EQ(0, solution.findLHS({1, 1, 1, 1}));
}

}