#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minCost(std::string const &colors, std::vector<int> const &neededTime) const
    {
        int totalSum = 0;
        size_t groupStart = 0;
        int maxGroupValue = 0;
        int groupSum = 0;
        for (size_t index = 0; index < colors.size(); ++index)
        {
            if (colors[groupStart] == colors[index])
            {
                if (neededTime[index] > maxGroupValue)
                {
                    groupSum += maxGroupValue;
                    maxGroupValue = neededTime[index];
                }
                else
                    groupSum += neededTime[index];
            }
            else
            {
                totalSum += groupSum;
                groupStart = index;
                maxGroupValue = neededTime[index];
                groupSum = 0;
            }
        }
        totalSum += groupSum;
        return totalSum;
    }
};

}

namespace MinTimeToMakeRopeColorfulTask
{

TEST(MinTimeToMakeRopeColorfulTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minCost("abaac", {1, 2, 3, 4, 5}));
    ASSERT_EQ(0, solution.minCost("abc", {1, 2, 3}));
    ASSERT_EQ(2, solution.minCost("aabaa", {1, 2, 3, 4, 1}));
}

}