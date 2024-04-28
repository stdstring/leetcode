#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int partitionArray(std::vector<int> const &nums, int k) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        size_t partitionCount = 1;
        for (size_t start = 0, end = 0; end < numbers.size(); ++end)
        {
            if ((numbers[end] - numbers[start]) > k)
            {
                start = end;
                ++partitionCount;
            }
        }
        return static_cast<int>(partitionCount);
    }
};

}

namespace PartitionArraySuchMaxDiffKTask
{

TEST(PartitionArraySuchMaxDiffKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.partitionArray({3, 6, 1, 2, 5}, 2));
    ASSERT_EQ(2, solution.partitionArray({1, 2, 3}, 1));
    ASSERT_EQ(3, solution.partitionArray({2, 2, 4, 5}, 0));
}

}