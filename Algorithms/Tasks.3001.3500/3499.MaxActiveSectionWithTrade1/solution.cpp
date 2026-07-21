#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxActiveSectionsAfterTrade(std::string const &s) const
    {
        typedef std::pair<size_t, char> Segment;
        std::vector<Segment> segments;
        segments.emplace_back(0, s[0]);
        for (const char ch : s)
        {
            if (ch == segments.back().second)
                ++segments.back().first;
            else
                segments.emplace_back(1, ch);
        }
        const size_t onesCount = std::ranges::count(s, '1');
        size_t result = onesCount;
        for (size_t index = segments.front().second == '0' ? 1 : 2; index < segments.size(); index+=2)
        {
            if (index == (segments.size() - 1))
                break;
            size_t current = onesCount;
            if (index > 0)
                current += segments[index - 1].first;
            if ((index + 1) < segments.size())
                current += segments[index + 1].first;
            result = std::max(result, current);
        }
        return static_cast<int>(result);
    }
};

}

namespace MaxActiveSectionWithTrade1Task
{

TEST(MaxActiveSectionWithTrade1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.maxActiveSectionsAfterTrade("01"));
    ASSERT_EQ(4, solution.maxActiveSectionsAfterTrade("0100"));
    ASSERT_EQ(7, solution.maxActiveSectionsAfterTrade("1000100"));
    ASSERT_EQ(4, solution.maxActiveSectionsAfterTrade("01010"));
}

TEST(MaxActiveSectionWithTrade1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.maxActiveSectionsAfterTrade("10100101"));
}

}
