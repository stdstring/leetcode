#include <algorithm>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minInsertions(std::string const &s) const
    {
        std::unordered_map<size_t, int> dp;
        return minInsertions(s, 0, s.size() - 1, dp);
    }

private:
    [[nodiscard]] int minInsertions(std::string const &s, size_t start, size_t finish, std::unordered_map<size_t, int> &dp) const
    {
        if (start >= finish)
            return 0;
        constexpr size_t factor = 1000;
        const size_t id = start * factor + finish;
        const auto iterator = dp.find(id);
        if (iterator != dp.cend())
            return iterator->second;
        const int value = s[start] == s[finish] ?
                          minInsertions(s, start + 1, finish - 1, dp) :
                          1 + std::min(minInsertions(s, start + 1, finish, dp), minInsertions(s, start, finish - 1, dp));
        dp.emplace(id, value);
        return value;
    }
};

}

namespace MinInsertionStepsMakeStringPalindromeTask
{

TEST(MinInsertionStepsMakeStringPalindromeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minInsertions("zzazz"));
    ASSERT_EQ(2, solution.minInsertions("mbadm"));
    ASSERT_EQ(5, solution.minInsertions("leetcode"));
}

TEST(MinInsertionStepsMakeStringPalindromeTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minInsertions("zjveiiwvc"));
    ASSERT_EQ(25, solution.minInsertions("tldjbqjdogipebqsohdypcxjqkrqltpgviqtqz"));
}

}