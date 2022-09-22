#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int arraySign(std::vector<int> const &nums) const
    {
        int result = 1;
        for (const int number : nums)
        {
            if (number == 0)
                return 0;
            result *= (number > 0 ? 1 : -1);
        }
        return result;
    }
};

}

namespace SignOfProductOfArrayTask
{

TEST(SignOfProductOfArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.arraySign({-1, -2, -3, -4, 3, 2, 1}));
    ASSERT_EQ(0, solution.arraySign({1, 5, 0, 2, -3}));
    ASSERT_EQ(-1, solution.arraySign({-1, 1, -1, 1, -1}));
}

TEST(SignOfProductOfArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.arraySign({51, 38, 73, 21, 27, 55, 18, 15, 79, 29, 13, 45, 8, -73, -92, -20, -50, -60, -70}));
}

}