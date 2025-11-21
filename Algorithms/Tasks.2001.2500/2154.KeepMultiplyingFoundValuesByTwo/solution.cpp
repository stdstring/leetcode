#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findFinalValue(std::vector<int> const &nums, int original) const
    {
        std::unordered_set<int> numbers(nums.cbegin(), nums.cend());
        while (numbers.contains(original))
            original *= 2;
        return original;
    }
};

}

namespace KeepMultiplyingFoundValuesByTwoTask
{

TEST(KeepMultiplyingFoundValuesByTwoTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(24, solution.findFinalValue({5, 3, 6, 1, 12}, 3));
    ASSERT_EQ(4, solution.findFinalValue({2, 7, 9}, 4));
}

}