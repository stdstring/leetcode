#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maximumHappinessSum(std::vector<int> const &happiness, int k) const
    {
        std::vector<int> sortedHappiness(happiness);
        std::ranges::sort(sortedHappiness, std::greater<int>());
        long long result = 0;
        int iteration = 0;
        for (const int value : sortedHappiness)
        {
            if ((iteration == k) || (value <= iteration))
                break;
            result += (value - iteration);
            ++iteration;
        }
        return result;
    }
};

}

namespace MaxHappinessOfSelectedChildrenTask
{

TEST(MaxHappinessOfSelectedChildrenTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maximumHappinessSum({1, 2, 3}, 2));
    ASSERT_EQ(1, solution.maximumHappinessSum({1, 1, 1, 1}, 2));
    ASSERT_EQ(5, solution.maximumHappinessSum({2, 3, 4, 5}, 1));
}

}