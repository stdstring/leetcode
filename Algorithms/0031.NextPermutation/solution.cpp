#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void nextPermutation(std::vector<int> &nums)
    {
        if (nums.size() == 1)
            return;
        size_t j = nums.size();
        for (size_t index = 0; index < nums.size() - 1; ++index)
        {
            if (nums[index] < nums[index + 1])
                j = index;
        }
        if (j == nums.size())
            std::sort(nums.begin(), nums.end());
        else
        {
            size_t l = j;
            for (size_t index = j + 1; index < nums.size(); ++index)
            {
                if (nums[j] < nums[index])
                    l = index;
            }
            std::swap(nums[j], nums[l]);
            std::vector<int>::iterator start = nums.begin();
            std::advance(start, j + 1);
            std::reverse(start, nums.end());
        }
    }
};

}

namespace NextPermutationTask
{

void checkNextPermutation(std::vector<int> const &initial, std::vector<int> const &expected)
{
    Solution solution;
    std::vector<int> next(initial);
    solution.nextPermutation(next);
    ASSERT_EQ(expected, next);
}

TEST(NextPermutationTaskTests, Examples)
{
    checkNextPermutation({1, 2, 3}, {1, 3, 2});
    checkNextPermutation({3, 2, 1}, {1, 2, 3});
    checkNextPermutation({1, 1, 5}, {1, 5, 1});
    checkNextPermutation({1}, {1});
}

}