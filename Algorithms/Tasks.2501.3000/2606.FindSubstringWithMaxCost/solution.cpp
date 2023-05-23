#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumCostSubstring(std::string const &s, std::string const &chars, std::vector<int> const &vals) const
    {
        // Kadane’s Algorithm
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<int> charValues(alphabetSize, 0);
        std::iota(charValues.begin(), charValues.end(), 1);
        for (size_t index = 0; index < chars.size(); ++index)
            charValues[chars[index] - alphabetStart] = vals[index];
        int currentSum = 0;
        int maxSum = INT_MIN;
        for (const char ch : s)
        {
            currentSum += charValues[ch - alphabetStart];
            if (currentSum < 0)
                currentSum = 0;
            maxSum = std::max(maxSum, currentSum);
        }
        return maxSum;
    }
};

}

namespace FindSubstringWithMaxCostTask
{

TEST(FindSubstringWithMaxCostTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maximumCostSubstring("adaa", "d", {-1000}));
    ASSERT_EQ(0, solution.maximumCostSubstring("abc", "abc", {-1, -1, -1}));
}

}