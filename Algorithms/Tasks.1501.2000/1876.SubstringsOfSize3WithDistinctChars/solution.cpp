#include <algorithm>
#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countGoodSubstrings(std::string const &s) const
    {
        constexpr size_t substringSize = 3;
        if (s.size() < substringSize)
            return 0;
        size_t count = 0;
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        for (size_t index = 0; index < substringSize; ++index)
            ++letterData[s[index] - AlphabetStart];
        if (isGoodSubstring(letterData))
            ++count;
        for (size_t index = substringSize; index < s.size(); ++index)
        {
            --letterData[s[index - substringSize] - AlphabetStart];
            ++letterData[s[index] - AlphabetStart];
            if (isGoodSubstring(letterData))
                ++count;
        }
        return static_cast<int>(count);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    [[nodiscard]] bool isGoodSubstring(std::array<size_t, AlphabetSize> const &letterData) const
    {
        return std::all_of(letterData.cbegin(), letterData.cend(), [](size_t count) { return count <= 1; });
    }
};

}

namespace SubstringsOfSize3WithDistinctCharsTask
{

TEST(SubstringsOfSize3WithDistinctCharsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.countGoodSubstrings("xyzzaz"));
    ASSERT_EQ(4, solution.countGoodSubstrings("aababcabc"));
}

}
