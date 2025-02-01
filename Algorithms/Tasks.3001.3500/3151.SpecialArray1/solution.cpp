#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isArraySpecial(std::vector<int> const &nums) const
    {
        for (size_t index = 1; index < nums.size(); ++index)
        {
            int prevParity = nums[index - 1] % 2;
            int currentParity = nums[index] % 2;
            if (prevParity == currentParity)
                return false;
        }
        return true;
    }
};

}

namespace SpecialArray1Task
{

TEST(SpecialArray1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isArraySpecial({1}));
    ASSERT_EQ(true, solution.isArraySpecial({2, 1, 4}));
    ASSERT_EQ(false, solution.isArraySpecial({4, 3, 1, 6}));
}

}