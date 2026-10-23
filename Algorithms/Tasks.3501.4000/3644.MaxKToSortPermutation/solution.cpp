#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int sortPermutation(std::vector<int> const &nums) const
    {
        const int n = static_cast<int>(nums.size());
        int k = 0b1111111111111111111111111111111;
        bool isSorted = true;
        for (int current = 0; current < n; ++current)
        {
            if (current != nums[current])
            {
                isSorted = false;
                k &= nums[current];
            }
        }
        return isSorted ? 0 : k;
    }
};

}

namespace MaxKToSortPermutationTask
{

TEST(MaxKToSortPermutationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.sortPermutation({0, 3, 2, 1}));
    ASSERT_EQ(2, solution.sortPermutation({0, 1, 3, 2}));
    ASSERT_EQ(0, solution.sortPermutation({3, 2, 1, 0}));
}

TEST(MaxKToSortPermutationTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.sortPermutation({0, 1}));
}

}