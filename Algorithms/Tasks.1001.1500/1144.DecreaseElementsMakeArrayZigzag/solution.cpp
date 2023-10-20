#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int movesToMakeZigzag(std::vector<int> const &nums) const
    {
        // A[0] < A[1] > A[2] < A[3] > A[4] < ...
        int movesCase1 = 0;
        // A[0] > A[1] < A[2] > A[3] < A[4] > ...
        int movesCase2 = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            int current = nums[index];
            int& moves = (index % 2) == 0 ? movesCase1 : movesCase2;
            if ((index > 0) && (current >= nums[index - 1]))
            {
                moves += (current - nums[index - 1] + 1);
                current = nums[index - 1] - 1;
            }
            if ((index < (nums.size() - 1)) && (current >= nums[index + 1]))
                moves += (current - nums[index + 1] + 1);
        }
        return std::min(movesCase1, movesCase2);
    }
};

}

namespace DecreaseElementsMakeArrayZigzagTask
{

TEST(DecreaseElementsMakeArrayZigzagTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.movesToMakeZigzag({1, 2, 3}));
    ASSERT_EQ(4, solution.movesToMakeZigzag({9, 6, 1, 6, 2}));
}

}