#include <algorithm>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumSetSize(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        const size_t n = nums1.size();
        const size_t maxSetSize = n / 2;
        const std::unordered_set<int> numberSet1(nums1.cbegin(), nums1.cend());
        const std::unordered_set<int> numberSet2(nums2.cbegin(), nums2.cend());
        std::unordered_set<int> numberIntersection;
        for (int number : nums1)
        {
            if (numberSet2.contains(number))
                numberIntersection.insert(number);
        }
        size_t commonSize = numberIntersection.size();
        const size_t rest1Size = numberSet1.size() - commonSize;
        const size_t rest2Size = numberSet2.size() - commonSize;
        size_t result1Size = rest1Size > maxSetSize ? maxSetSize : rest1Size;
        if (result1Size < maxSetSize)
        {
            result1Size += std::min(commonSize, maxSetSize - rest1Size);
            commonSize -= std::min(commonSize, maxSetSize - rest1Size);
        }
        size_t result2Size = rest2Size > maxSetSize ? maxSetSize : rest2Size;
        if (result2Size < maxSetSize)
        {
            result2Size += std::min(commonSize, maxSetSize - rest2Size);
            commonSize -= std::min(commonSize, maxSetSize - rest2Size);
        }
        return static_cast<int>(result1Size + result2Size);
    }
};

}

namespace MaxSizeSetAfterRemovalsTask
{

TEST(MaxSizeSetAfterRemovalsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maximumSetSize({1, 2, 1, 2}, {1, 1, 1, 1}));
    ASSERT_EQ(5, solution.maximumSetSize({1, 2, 3, 4, 5, 6}, {2, 3, 2, 3, 2, 3}));
    ASSERT_EQ(6, solution.maximumSetSize({1, 1, 2, 2, 3, 3}, {4, 4, 5, 5, 6, 6}));
}

}