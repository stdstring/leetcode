#include <algorithm>
#include <map>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string smallestPalindrome(std::string const &s) const
    {
        std::map<char, size_t> symbolMap;
        for (char ch : s)
            ++symbolMap[ch];
        std::string result;
        char middle = '\0';
        for (auto const &[ch, count]: symbolMap)
        {
            result.append(count / 2, ch);
            if ((count % 2) == 1)
                middle = ch;
        }
        std::string rightPart(result);
        std::ranges::reverse(rightPart);
        if ((s.size() % 2) == 1)
            result.push_back(middle);
        result.append(rightPart);
        return result;
    }
};

}

namespace SmallestPalindromicRearrangement1Task
{

TEST(SmallestPalindromicRearrangement1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("z", solution.smallestPalindrome("z"));
    ASSERT_EQ("abbba", solution.smallestPalindrome("babab"));
    ASSERT_EQ("acddca", solution.smallestPalindrome("daccad"));
}

}