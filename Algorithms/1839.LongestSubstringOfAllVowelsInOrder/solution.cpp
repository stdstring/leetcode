#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestBeautifulSubstring(std::string const &word) const
    {
        constexpr size_t alphabetSize = 256;
        std::array<uint8_t, alphabetSize> nextCharMap{};
        nextCharMap.fill(0);
        nextCharMap[0] = 'a';
        nextCharMap['a'] = 'e';
        nextCharMap['e'] = 'i';
        nextCharMap['i'] = 'o';
        nextCharMap['o'] = 'u';
        constexpr uint8_t startChar = 'a';
        constexpr uint8_t lastChar = 'u';
        size_t beautifulSize = 0;
        uint8_t currentChar = 0;
        size_t currentSize = 0;
        for (const uint8_t ch : word)
        {
            if ((ch == currentChar) || (ch == nextCharMap[currentChar]))
            {
                ++currentSize;
                currentChar = ch;
            }
            else
            {
                if (currentChar == lastChar)
                    beautifulSize = std::max(beautifulSize, currentSize);
                currentSize = ch == startChar ? 1 : 0;
                currentChar = ch == startChar ? startChar : 0;
            }
        }
        if (currentChar == lastChar)
            beautifulSize = std::max(beautifulSize, currentSize);
        return static_cast<int>(beautifulSize);
    }
};

}

namespace LongestSubstringOfAllVowelsInOrderTask
{

TEST(LongestSubstringOfAllVowelsInOrderTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(13, solution.longestBeautifulSubstring("aeiaaioaaaaeiiiiouuuooaauuaeiu"));
    ASSERT_EQ(5, solution.longestBeautifulSubstring("aeeeiiiioooauuuaeiou"));
    ASSERT_EQ(0, solution.longestBeautifulSubstring("a"));
}

}
