#include <algorithm>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums, int k) const
    {
        int minValue = INT_MAX;
        std::unordered_set<int> knownNumbers;
        for (int number : nums)
        {
            if (number < k)
                return -1;
            knownNumbers.emplace(number);
            minValue = std::min(minValue, number);
        }
        return static_cast<int>(knownNumbers.size() - ((k == minValue) ? 1 : 0));
    }
};

}

namespace MinOperationsMakeArrayValuesEqualKTask
{

TEST(MinOperationsMakeArrayValuesEqualKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations({5, 2, 5, 4, 5}, 2));
    ASSERT_EQ(-1, solution.minOperations({2, 1, 2}, 2));
    ASSERT_EQ(4, solution.minOperations({9, 7, 5, 3}, 1));
}

}