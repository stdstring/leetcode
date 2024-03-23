#include <algorithm>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestCommonPrefix(std::vector<int> const &arr1, std::vector<int> const &arr2) const
    {
        std::unordered_set<int> prefixes;
        for (const int number : arr1)
        {
            for (int factor = getMaxDigitFactor(number); factor > 0; factor /= 10)
                prefixes.emplace(number / factor);
        }
        std::unordered_set<int> commonPrefixes;
        for (const int number : arr2)
        {
            for (int factor = getMaxDigitFactor(number); factor > 0; factor /= 10)
            {
                int prefix = number / factor;
                if (!prefixes.contains(prefix))
                    break;
                commonPrefixes.emplace(prefix);
            }
        }
        if (commonPrefixes.empty())
            return 0;
        int maxPrefix = *std::ranges::max_element(commonPrefixes);
        size_t maxPrefixSize = 0;
        while (maxPrefix > 0)
        {
            maxPrefix /= 10;
            ++maxPrefixSize;
        }
        return static_cast<int>(maxPrefixSize);
    }

private:
    [[nodiscard]] int getMaxDigitFactor(int number) const
    {
        int factor = 1;
        while ((number / factor) > 9)
            factor *= 10;
        return factor;
    }
};

}

namespace FindLengthLongestCommonPrefixTask
{

TEST(FindLengthLongestCommonPrefixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.longestCommonPrefix({1, 10, 100}, {1000}));
    ASSERT_EQ(0, solution.longestCommonPrefix({1, 2, 3}, {4, 4, 4}));
}

TEST(FindLengthLongestCommonPrefixTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.longestCommonPrefix({1, 22, 333}, {22, 310}));
}

}