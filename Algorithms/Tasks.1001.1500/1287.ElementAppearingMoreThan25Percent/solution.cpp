#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findSpecialInteger(std::vector<int> const &arr) const
    {
        size_t start = 0;
        for (size_t index = 0; index < arr.size(); ++index)
        {
            if (arr[start] != arr[index])
            {
                const size_t portionSize = index - start;
                if (4 * portionSize > arr.size())
                    return arr[start];
                start = index;
            }
        }
        return arr[start];
    }
};

}

namespace ElementAppearingMoreThan25PercentTask
{

TEST(ElementAppearingMoreThan25PercentTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.findSpecialInteger({1, 2, 2, 6, 6, 6, 6, 7, 10}));
    ASSERT_EQ(1, solution.findSpecialInteger({1, 1}));
}

}