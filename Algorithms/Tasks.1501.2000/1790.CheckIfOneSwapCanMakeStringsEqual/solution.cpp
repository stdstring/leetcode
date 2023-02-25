#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool areAlmostEqual(std::string const &s1, std::string const &s2) const
    {
        std::vector<std::pair<char, char>> diffPairs;
        for (size_t index = 0; index < s1.size(); ++index)
        {
            if (s1[index] != s2[index])
            {
                if (diffPairs.size() == 2)
                    return false;
                diffPairs.emplace_back(s1[index], s2[index]);
            }
        }
        if (diffPairs.empty())
            return true;
        if (diffPairs.size() == 1)
            return false;
        return (diffPairs[0].first == diffPairs[1].second) && (diffPairs[0].second == diffPairs[1].first);
    }
};

}

namespace CheckIfOneSwapCanMakeStringsEqualTask
{

TEST(CheckIfOneSwapCanMakeStringsEqualTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.areAlmostEqual("bank", "kanb"));
    ASSERT_EQ(false, solution.areAlmostEqual("attack", "defend"));
    ASSERT_EQ(true, solution.areAlmostEqual("kelb", "kelb"));
    ASSERT_EQ(false, solution.areAlmostEqual("abcd", "dcba"));
}

}