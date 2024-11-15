#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findLengthOfShortestSubarray(std::vector<int> const &arr) const
    {
        size_t suffixStart = arr.size() - 1;
        for (;(suffixStart > 0) && (arr[suffixStart - 1] <= arr[suffixStart]); --suffixStart) {}
        if (suffixStart == 0)
            return 0;
        size_t deletedSize = suffixStart;
        size_t prefixEnd = 0;
        do
        {
            for(;(suffixStart < arr.size()) && (arr[suffixStart] < arr[prefixEnd]); ++suffixStart) {}
            deletedSize = std::min(deletedSize, suffixStart - prefixEnd - 1);
            ++prefixEnd;
        } while (arr[prefixEnd - 1] <= arr[prefixEnd]);
        return static_cast<int>(deletedSize);
    }
};

}

namespace ShortestSubarrayRemovedToMakeArraySortedTask
{

TEST(ShortestSubarrayRemovedToMakeArraySortedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.findLengthOfShortestSubarray({1, 2, 3, 10, 4, 2, 3, 5}));
    ASSERT_EQ(4, solution.findLengthOfShortestSubarray({5, 4, 3, 2, 1}));
    ASSERT_EQ(0, solution.findLengthOfShortestSubarray({1, 2, 3}));
}

}