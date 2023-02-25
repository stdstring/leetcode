#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool arrayStringsAreEqual(std::vector<std::string> const &word1, std::vector<std::string> const &word2) const
    {
        size_t index1 = 0;
        size_t index2 = 0;
        size_t str1Index = 0;
        size_t str2Index = 0;
        while ((index1 < word1.size()) && (index2 < word2.size()))
        {
            if (word1[index1][str1Index] != word2[index2][str2Index])
                return false;
            ++str1Index;
            if (str1Index == word1[index1].size())
            {
                ++index1;
                str1Index = 0;
            }
            ++str2Index;
            if (str2Index == word2[index2].size())
            {
                ++index2;
                str2Index = 0;
            }
        }
        return (index1 == word1.size()) && (index2 == word2.size());
    }
};

}

namespace CheckIfTwoStringArraysEquivalentTask
{

TEST(CheckIfTwoStringArraysEquivalentTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.arrayStringsAreEqual({"ab", "c"}, {"a", "bc"}));
    ASSERT_EQ(false, solution.arrayStringsAreEqual({"a", "cb"}, {"ab", "c"}));
    ASSERT_EQ(true, solution.arrayStringsAreEqual({"abc", "d", "defg"}, {"abcddefg"}));
}

}