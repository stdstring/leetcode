#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findPeakElement(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return 0;
        if (nums[0] > nums[1])
            return 0;
        for (size_t index = 1; index < nums.size() - 1; ++index)
        {
            if ((nums[index - 1] < nums[index]) && (nums[index + 1] < nums[index]))
                return static_cast<int>(index);
        }
        return static_cast<int>(nums.size() - 1);
    }
};

}

namespace FindPeakElementTask
{

TEST(FindPeakElementTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findPeakElement({1, 2, 3, 1}));
    ASSERT_EQ(1, solution.findPeakElement({1, 2, 1, 3, 5, 6, 4}));
}

TEST(FindPeakElementTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.findPeakElement({1}));
    ASSERT_EQ(1, solution.findPeakElement({1, 2}));
}

}