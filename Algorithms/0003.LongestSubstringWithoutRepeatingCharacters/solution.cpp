#include <algorithm>
#include <array>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int lengthOfLongestSubstring(std::string const &s) const
    {
        constexpr int alphabetSize = 128;
        std::array<bool, alphabetSize> alphabetUsageData{};
        alphabetUsageData.fill(false);
        int maxSubstrLength = 0;
        size_t start = 0;
        size_t finish = 0;
        while (finish < s.size())
        {
            if (alphabetUsageData[s[finish]])
            {
                maxSubstrLength = std::max(maxSubstrLength, static_cast<int>(finish - start));
                while (alphabetUsageData[s[finish]])
                    alphabetUsageData[s[start++]] = false;
                alphabetUsageData[s[finish]] = true;
            }
            else
                alphabetUsageData[s[finish]] = true;
            ++finish;
        }
        maxSubstrLength = std::max(maxSubstrLength, static_cast<int>(finish - start));
        return maxSubstrLength;
    }
};

}

namespace LongestSubstringWithoutRepeatingCharactersTask
{

TEST(LongestSubstringWithoutRepeatingCharactersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.lengthOfLongestSubstring("abcabcbb"));
    ASSERT_EQ(1, solution.lengthOfLongestSubstring("bbbbb"));
    ASSERT_EQ(3, solution.lengthOfLongestSubstring("pwwkew"));
    ASSERT_EQ(0, solution.lengthOfLongestSubstring(""));
}


}