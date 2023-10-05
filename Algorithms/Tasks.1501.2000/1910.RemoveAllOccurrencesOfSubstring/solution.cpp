#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string removeOccurrences(std::string const &s, std::string const &part) const
    {
        std::string dest;
        dest.reserve(s.size());
        for (const char ch : s)
        {
            dest.push_back(ch);
            if (dest.ends_with(part))
                dest.erase(dest.size() - part.size());
        }
        return dest;
    }
};

}

namespace RemoveAllOccurrencesOfSubstringTask
{

TEST(RemoveAllOccurrencesOfSubstringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("dab", solution.removeOccurrences("daabcbaabcbc", "abc"));
    ASSERT_EQ("ab", solution.removeOccurrences("axxxxyyyyb", "xy"));
}

}