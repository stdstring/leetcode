#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumDeletions(std::vector<int> const &nums) const
    {
        if (nums.size() < 3)
            return static_cast<int>(nums.size());
        size_t minIndex = 0;
        size_t maxIndex = 0;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index] < nums[minIndex])
                minIndex = index;
            if (nums[index] > nums[maxIndex])
                maxIndex = index;
        }
        const size_t removeLeft = std::max(minIndex, maxIndex) + 1;
        const size_t removeRight = nums.size() - std::min(minIndex, maxIndex);
        const size_t removeLeftRight = (std::min(minIndex, maxIndex) + 1) +
                                       (nums.size() - std::max(minIndex, maxIndex));
        return static_cast<int>(std::min({removeLeft, removeRight, removeLeftRight}));
    }
};

}

namespace RemovingMinMaxFromArrayTask
{

TEST(RemovingMinMaxFromArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minimumDeletions({2, 10, 7, 5, 4, 1, 8, 6}));
    ASSERT_EQ(3, solution.minimumDeletions({0, -4, 19, 1, 8, -2, -3, 5}));
    ASSERT_EQ(1, solution.minimumDeletions({101}));
}

}