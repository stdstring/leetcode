#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int xorAllNums(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        int result = 0;
        if ((nums2.size() % 2) == 1)
        {
            for (const int number : nums1)
                result ^= number;
        }
        if ((nums1.size() % 2) == 1)
        {
            for (const int number : nums2)
                result ^= number;
        }
        return result;
    }
};

}

namespace BitwiseXORAllPairingsTask
{

TEST(BitwiseXORAllPairingsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.xorAllNums({2, 1, 3}, {10, 2, 5, 0}));
    ASSERT_EQ(0, solution.xorAllNums({1, 2}, {3, 4}));
}

TEST(BitwiseXORAllPairingsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(26, solution.xorAllNums({2, 22, 3}, {10, 2, 5}));
}

}