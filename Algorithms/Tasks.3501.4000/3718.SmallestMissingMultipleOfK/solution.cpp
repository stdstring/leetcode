#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int missingMultiple(std::vector<int> const &nums, int k) const
    {
        const std::unordered_set numbers(nums.cbegin(), nums.cend());
        for (int multiplier = 1;; ++multiplier)
        {
            int current = k * multiplier;
            if (!numbers.contains(current))
                return current;
        }
    }
};

}

namespace SmallestMissingMultipleOfKTask
{

TEST(SmallestMissingMultipleOfKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(10, solution.missingMultiple({8, 2, 3, 4, 6}, 2));
    ASSERT_EQ(5, solution.missingMultiple({1, 4, 7, 10, 15}, 5));
}

}