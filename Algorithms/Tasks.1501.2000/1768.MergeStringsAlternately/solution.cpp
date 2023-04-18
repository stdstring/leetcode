#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string mergeAlternately(std::string const &word1, std::string const &word2) const
    {
        std::string result;
        result.reserve(word1.size() + word2.size());
        for (size_t index1 = 0, index2 = 0; (index1 < word1.size()) || (index2 < word2.size());)
        {
            if (index1 < word1.size())
                result.push_back(word1[index1++]);
            if (index2 < word2.size())
                result.push_back(word2[index2++]);
        }
        return result;
    }
};

}

namespace MergeStringsAlternatelyTask
{

TEST(MergeStringsAlternatelyTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("apbqcr", solution.mergeAlternately("abc", "pqr"));
    ASSERT_EQ("apbqrs", solution.mergeAlternately("ab", "pqrs"));
    ASSERT_EQ("apbqcd", solution.mergeAlternately("abcd", "pq"));
}

}