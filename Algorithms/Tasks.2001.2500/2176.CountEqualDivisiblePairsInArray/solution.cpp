#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countPairs(std::vector<int> const &nums, int k) const
    {
        size_t result = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            for (size_t j = i + 1; j < nums.size(); ++j)
            {
                if ((nums[i] == nums[j]) && ((i * j) % k == 0))
                    ++result;
            }
        }
        return static_cast<int>(result);
    }
};

}

namespace CountEqualDivisiblePairsInArrayTask
{

TEST(CountEqualDivisiblePairsInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countPairs({3, 1, 2, 2, 2, 1, 3}, 2));
    ASSERT_EQ(0, solution.countPairs({1, 2, 3, 4}, 1));
}

}