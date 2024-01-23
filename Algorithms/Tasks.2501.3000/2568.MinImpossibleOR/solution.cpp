#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minImpossibleOR(std::vector<int> const &nums) const
    {
        const std::unordered_set<int> numbers(nums.cbegin(), nums.cend());
        for (int number = 1;; number <<= 1)
        {
            if (!numbers.contains(number))
                return number;
        }
    }
};

}

namespace MinImpossibleORTask
{

TEST(MinImpossibleORTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minImpossibleOR({2, 1}));
    ASSERT_EQ(1, solution.minImpossibleOR({5, 3, 2}));
}

}