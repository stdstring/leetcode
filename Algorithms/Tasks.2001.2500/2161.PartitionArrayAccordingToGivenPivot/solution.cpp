#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> pivotArray(std::vector<int> const &nums, int pivot) const
    {
        std::vector<int> result(nums.size(), pivot);
        size_t resultIndex = 0;
        for (const int number : nums)
        {
            if (number < pivot)
                result[resultIndex++] = number;
        }
        resultIndex = result.size() - 1;
        for (auto iterator = nums.crbegin(); iterator != nums.crend(); ++iterator)
        {
            if (*iterator > pivot)
                result[resultIndex--] = *iterator;
        }
        return result;
    }
};

}

namespace PartitionArrayAccordingToGivenPivotTask
{

TEST(PartitionArrayAccordingToGivenPivotTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({9, 5, 3, 10, 10, 12, 14}), solution.pivotArray({9, 12, 5, 10, 14, 3, 10}, 10));
    ASSERT_EQ(std::vector<int>({-3, 2, 4, 3}), solution.pivotArray({-3, 4, 3, 2}, 2));
}

}