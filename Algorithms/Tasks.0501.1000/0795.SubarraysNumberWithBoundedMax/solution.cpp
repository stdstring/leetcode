#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSubarrayBoundedMax(std::vector<int> const &nums, int left, int right) const
    {
        size_t subarrayCount = 0;
        size_t begin = 0;
        std::vector<size_t> maxPositions;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if ((left <= nums[index]) && (nums[index] <= right))
                maxPositions.emplace_back(index);
            if (right < nums[index])
            {
                subarrayCount += calcSubarrayCount(begin, index, maxPositions);
                maxPositions.clear();
                begin = index + 1;
            }
        }
        subarrayCount += calcSubarrayCount(begin, nums.size(), maxPositions);
        return static_cast<int>(subarrayCount);
    }

private:
    [[nodiscard]] size_t calcSubarrayCount(size_t begin, size_t end, std::vector<size_t> const &maxPositions) const
    {
        size_t subarrayCount = 0;
        for (const size_t currentMax : maxPositions)
        {
            const size_t beforeCount = currentMax - begin + 1;
            const size_t afterCount = end - (currentMax + 1) + 1;
            subarrayCount += (beforeCount * afterCount);
            begin = currentMax + 1;
        }
        return subarrayCount;
    }
};

}

namespace SubarraysNumberWithBoundedMaxTask
{

TEST(SubarraysNumberWithBoundedMaxTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numSubarrayBoundedMax({2, 1, 4, 3}, 2, 3));
    ASSERT_EQ(7, solution.numSubarrayBoundedMax({2, 9, 2, 5, 6}, 2, 8));
}

}