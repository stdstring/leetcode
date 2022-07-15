#include <array>
#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int characterReplacement(std::string const &s, int k) const
    {
        size_t maxSubstring = 0;
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        size_t start = 0;
        for (size_t end = 0; end < s.size(); ++end)
        {
            ++letterData[s[end] - AlphabetStart];
            while (!isAllowedSubstring(s, end - start + 1, k, letterData))
            {
                --letterData[s[start] - AlphabetStart];
                ++start;
            }
            maxSubstring = std::max(maxSubstring, end - start + 1);
        }
        return static_cast<int>(maxSubstring);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'A';

    [[nodiscard]] bool isAllowedSubstring(std::string const &s, size_t size, size_t maxReplace, std::array<size_t, AlphabetSize> const &letterData) const
    {
        const size_t maxCharSize = *std::max_element(letterData.cbegin(), letterData.cend());
        return (size - maxCharSize) <= maxReplace;
    }
};

}

namespace LongestRepeatingCharReplacementTask
{

TEST(LongestRepeatingCharReplacementTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.characterReplacement("ABAB", 2));
    ASSERT_EQ(4, solution.characterReplacement("AABABBA", 1));
    ASSERT_EQ(2, solution.characterReplacement("AABABBA", 0));
    ASSERT_EQ(3, solution.characterReplacement("AABABBBA", 0));
}

}