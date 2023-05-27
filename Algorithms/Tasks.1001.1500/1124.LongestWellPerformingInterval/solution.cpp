#include <algorithm>
#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestWPI(std::vector<int> const &hours) const
    {
        std::map<int, size_t> balanceMap;
        int balance = 0;
        size_t bestSize = 0;
        for (size_t index = 0; index < hours.size(); ++index)
        {
            balance += (hours[index] > 8 ? 1 : -1);
            if (balance > 0)
                bestSize = (index + 1);
            else
            {
                auto iterator = balanceMap.cbegin();
                for (; (iterator != balanceMap.cend()) && (iterator->first < balance); ++iterator)
                    bestSize = std::max(bestSize, index - iterator->second);
                if ((iterator == balanceMap.cend()) || (iterator->first != balance))
                    balanceMap.emplace(balance, index);
            }
        }
        return static_cast<int>(bestSize);
    }
};

}

namespace LongestWellPerformingIntervalTask
{

TEST(LongestWellPerformingIntervalTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.longestWPI({9, 9, 6, 0, 6, 6, 9}));
    ASSERT_EQ(0, solution.longestWPI({6, 6, 6}));
}

TEST(LongestWellPerformingIntervalTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.longestWPI({6, 6, 9}));
}

}