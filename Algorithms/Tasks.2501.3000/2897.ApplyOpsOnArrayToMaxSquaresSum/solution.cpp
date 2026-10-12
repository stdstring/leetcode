#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSum(std::vector<int> const &nums, int k) const
    {
        // 10^9 = 00111011100110101100101000000000
        // most significant bit = 2^30
        constexpr int bitsCount = 30;
        std::vector<size_t> availableBits(bitsCount, 0);
        for (const int number : nums)
        {
            for (int bit = 0; bit < bitsCount; ++bit)
            {
                const int mask = 1 << bit;
                if (mask > number)
                    break;
                if ((number & mask) != 0)
                    ++availableBits[bit];
            }
        }
        constexpr int modValue = 1000000007;
        long long result = 0;
        for (int number = 0; number < k; ++number)
        {
            long long current = 0;
            for (int bit = 0; bit < bitsCount; ++bit)
            {
                if (availableBits[bit] > 0)
                {
                    current |= (1LL << bit);
                    --availableBits[bit];
                }
            }
            result = (result + current * current) % modValue;
        }
        return static_cast<int>(result);
    }
};

}

namespace ApplyOpsOnArrayToMaxSquaresSumTask
{

TEST(ApplyOpsOnArrayToMaxSquaresSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(261, solution.maxSum({2, 6, 5, 8}, 2));
    ASSERT_EQ(90, solution.maxSum({4, 5, 4, 7}, 3));
}

TEST(ApplyOpsOnArrayToMaxSquaresSumTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(49, solution.maxSum({1, 2, 4}, 1));
}

}