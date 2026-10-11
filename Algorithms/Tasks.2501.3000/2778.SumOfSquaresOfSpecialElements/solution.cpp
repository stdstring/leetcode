#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int sumOfSquares(std::vector<int> const &nums) const
    {
        int result = 0;
        for (size_t index1 = 1; index1 <= nums.size(); ++index1)
        {
            if ((nums.size() % index1) == 0)
                result += nums[index1 - 1] * nums[index1 - 1];
        }
        return result;
    }
};

}

namespace SumOfSquaresOfSpecialElementsTask
{

TEST(SumOfSquaresOfSpecialElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(21, solution.sumOfSquares({1, 2, 3, 4}));
    ASSERT_EQ(63, solution.sumOfSquares({2, 7, 1, 19, 18, 3}));
}

}