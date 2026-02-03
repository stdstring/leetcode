#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isTrionic(std::vector<int> const &nums) const
    {
        size_t current = 0;
        size_t p = 0;
        for (; current < nums.size() - 1; ++current)
        {
            p = current;
            if (nums[current] >= nums[current + 1])
                break;
        }
        if (p == 0)
            return false;
        size_t q = 0;
        for (; current < nums.size() - 1; ++current)
        {
            q = current;
            if (nums[current] <= nums[current + 1])
                break;
        }
        if (q == p)
            return false;
        bool hasThirdPart = false;
        for (; current < nums.size() - 1; ++current)
        {
            if (nums[current] >= nums[current + 1])
                return false;
            hasThirdPart = true;
        }
        return hasThirdPart;
    }
};

}

namespace TrionicArray1Task
{

TEST(TrionicArray1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isTrionic({1, 3, 5, 4, 2, 6}));
    ASSERT_EQ(false, solution.isTrionic({2, 1, 3}));
}

}