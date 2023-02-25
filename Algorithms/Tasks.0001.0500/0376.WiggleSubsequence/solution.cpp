#include <vector>

#include "gtest/gtest.h"

namespace
{

enum Difference { None, Positive, Negative };

class Solution
{
public:
    int wiggleMaxLength(std::vector<int> const &nums) const
    {
        if (nums.empty())
            return 0;
        size_t wiggleLength = 1;
        Difference difference = Difference::None;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index] == nums[index - 1])
                continue;
            const Difference currentDifference = nums[index] > nums[index - 1] ? Difference::Positive : Difference::Negative;
            if (currentDifference != difference)
            {
                difference = currentDifference;
                ++wiggleLength;
            }
        }
        return static_cast<int>(wiggleLength);
    }
};

}

namespace WiggleSubsequenceTask
{

TEST(WiggleSubsequenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.wiggleMaxLength({1, 7, 4, 9, 2, 5}));
    ASSERT_EQ(7, solution.wiggleMaxLength({1, 17, 5, 10, 13, 15, 10, 5, 16, 8}));
    ASSERT_EQ(2, solution.wiggleMaxLength({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(WiggleSubsequenceTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.wiggleMaxLength({}));
}


}