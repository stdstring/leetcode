#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int prefixCount(std::vector<std::string> const &words, std::string const &pref) const
    {
        size_t result = 0;
        for (std::string const &word : words)
        {
            if (word.starts_with(pref))
                ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace CountingWordsWithGivenPrefixTask
{

TEST(CountingWordsWithGivenPrefixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.prefixCount({"pay", "attention", "practice", "attend"}, "at"));
    ASSERT_EQ(0, solution.prefixCount({"leetcode", "win", "loops", "success"}, "code"));
}

}