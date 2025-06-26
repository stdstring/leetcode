#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestSubsequence(std::string const &s, int k) const
    {
        // 1000000000 == 00111011100110101100101000000000b
        constexpr size_t maxBitCount = 30;
        const long long maxValue = k;
        long long currentValue = 0;
        long long currentPower = 1;
        size_t subsequenceSize = 0;
        for (size_t rIndex = 0; rIndex < std::min(s.size(), maxBitCount + 1); ++rIndex)
        {
            const size_t index = s.size() - 1 - rIndex;
            if (currentValue <= maxValue)
            {
                currentValue += (s[index] == '0' ? 0 : 1) * currentPower;
                currentPower <<= 1;
            }
            if ((s[index] == '0') || (currentValue <= maxValue))
                ++subsequenceSize;
        }
        for (size_t rIndex = maxBitCount + 1; rIndex < s.size(); ++rIndex)
        {
            const size_t index = s.size() - 1 - rIndex;
            if (s[index] == '0')
                ++subsequenceSize;
        }
        return static_cast<int>(subsequenceSize);
    }
};

}

namespace LongestBinarySubsequenceLTE2KTask
{

TEST(LongestBinarySubsequenceLTE2KTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.longestSubsequence("1001010", 5));
    ASSERT_EQ(6, solution.longestSubsequence("00101001", 1));
}

}