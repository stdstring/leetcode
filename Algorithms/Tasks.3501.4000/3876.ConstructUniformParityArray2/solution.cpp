#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool uniformArray(std::vector<int> const &nums1) const
    {
        bool hasEven = false;
        bool hasOdd = false;
        int minEven = INT_MAX;
        int minOdd = INT_MAX;
        for (int number : nums1)
        {
            if ((number % 2) == 0)
            {
                hasEven = true;
                minEven = std::min(minEven, number);
            }
            if ((number % 2) == 1)
            {
                hasOdd = true;
                minOdd = std::min(minOdd, number);
            }
        }
        return !(hasEven && hasOdd) || (minOdd < minEven);
    }
};

}

namespace ConstructUniformParityArray2Task
{

TEST(ConstructUniformParityArray2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.uniformArray({1, 4, 7}));
    ASSERT_EQ(false, solution.uniformArray({2, 3}));
    ASSERT_EQ(true, solution.uniformArray({4, 6}));
}

}