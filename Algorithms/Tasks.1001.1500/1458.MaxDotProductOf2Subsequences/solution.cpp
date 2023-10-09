#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDotProduct(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        std::vector<std::vector<int>> dp(nums1.size(), std::vector<int>(nums2.size(), 0));
        bool isEmpty = true;
        int bestProduct = INT_MIN;
        for (size_t index1 = 0; index1 < nums1.size(); ++index1)
        {
            for (size_t index2 = 0; index2 < nums2.size(); ++index2)
            {
                const int product = nums1[index1] * nums2[index2];
                bestProduct = std::max(bestProduct, product);
                dp[index1][index2] = std::max(index1 > 0 ? dp[index1 - 1][index2] : 0, index2 > 0 ? dp[index1][index2 - 1] : 0);
                if (product >= 0)
                {
                    isEmpty = false;
                    dp[index1][index2] = std::max(dp[index1][index2], product + ((index1 > 0) && (index2 > 0) ? dp[index1 - 1][index2 - 1] : 0));
                }
            }
        }
        return isEmpty ? bestProduct : dp.back().back();
    }
};

}

namespace MaxDotProductOf2SubsequencesTask
{

TEST(MaxDotProductOf2SubsequencesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(18, solution.maxDotProduct({2, 1, -2, 5}, {3, 0, -6}));
    ASSERT_EQ(21, solution.maxDotProduct({3, -2}, {2, -6, 7}));
    ASSERT_EQ(-1, solution.maxDotProduct({-1, -1}, {1, 1}));
}

TEST(MaxDotProductOf2SubsequencesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(28, solution.maxDotProduct({5, -4, -3}, {-4, -3, 0, -4, 2}));
}

}