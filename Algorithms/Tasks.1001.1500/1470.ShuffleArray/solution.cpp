#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> shuffle(std::vector<int> const &nums, int n) const
    {
        const size_t border = n;
        std::vector<int> dest(2 * border, 0);
        for (size_t index = 0; index < border; ++index)
        {
            dest[2 * index] = nums[index];
            dest[2 * index + 1] = nums[border + index];
        }
        return dest;
    }
};

}

namespace ShuffleArrayTask
{

TEST(ShuffleArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 3, 5, 4, 1, 7}), solution.shuffle({2, 5, 1, 3, 4, 7}, 3));
    ASSERT_EQ(std::vector<int>({1, 4, 2, 3, 3, 2, 4, 1}), solution.shuffle({1, 2, 3, 4, 4, 3, 2, 1}, 4));
    ASSERT_EQ(std::vector<int>({1, 2, 1, 2}), solution.shuffle({1, 1, 2, 2}, 2));
}

}