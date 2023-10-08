#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestIdealString(std::string const &s, int k) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        const size_t delta = k;
        size_t bestSize = 0;
        std::vector<size_t> charSizes(alphabetSize, 0);
        for (const char ch : s)
        {
            const size_t currentIndex = ch - alphabetStart;
            size_t currentSize = 0;
            for (size_t charIndex = delta > currentIndex ? 0 : currentIndex - delta; charIndex < std::min(alphabetSize, currentIndex + delta + 1); ++charIndex)
                currentSize = std::max(currentSize, charSizes[charIndex]);
            charSizes[currentIndex] = currentSize + 1;
            bestSize = std::max(bestSize, charSizes[currentIndex]);
        }
        return static_cast<int>(bestSize);
    }
};

}

namespace LongestIdealSubsequenceTask
{

TEST(LongestIdealSubsequenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.longestIdealString("acfgbd", 2));
    ASSERT_EQ(4, solution.longestIdealString("abcd", 3));
}

}