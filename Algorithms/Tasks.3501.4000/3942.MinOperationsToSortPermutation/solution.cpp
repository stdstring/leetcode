#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return 0;
        size_t index0 = 0;
        while (nums[index0] != 0)
            ++index0;
        switch (calcDirection(nums, index0))
        {
            case Direction::None:
                return -1;
            case Direction::Left:
                return 1 + static_cast<int>(std::min(index0 + 1, nums.size() - index0 - 1));
            case Direction::Right:
                return static_cast<int>(std::min(index0, 2 + nums.size() - index0));
        }
        return -1;
    }

private:
    enum class Direction {None, Left, Right};

    [[nodiscard]] Direction calcDirection(std::vector<int> const &nums, size_t index0) const
    {
        const size_t nextIndex = (index0 + 1) % nums.size();
        if (nums[nextIndex] == 1)
        {
            int nextNumber = 1;
            for (size_t index = nextIndex; index != index0; index = (index + 1) % nums.size())
            {
                if (nums[index] != nextNumber)
                    return Direction::None;
                ++nextNumber;
            }
            return Direction::Right;
        }
        const size_t prevIndex = (nums.size() + index0 - 1) % nums.size();
        if (nums[prevIndex] == 1)
        {
            int prevNumber = 1;
            for (size_t index = prevIndex; index != index0; index = (nums.size() + index - 1) % nums.size())
            {
                if (nums[index] != prevNumber)
                    return Direction::None;
                ++prevNumber;
            }
            return Direction::Left;
        }
        return Direction::None;
    }
};

}

namespace MinOperationsToSortPermutationTask
{

TEST(MinOperationsToSortPermutationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations({0, 2, 1}));
    ASSERT_EQ(2, solution.minOperations({1, 0, 2}));
    ASSERT_EQ(-1, solution.minOperations({2, 0, 1, 3}));
}

TEST(MinOperationsToSortPermutationTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minOperations({1, 2, 3, 4, 0}));
}

}