#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string smallestEquivalentString(std::string const &s1, std::string const &s2, std::string const &baseStr) const
    {
        std::vector<int> parents(AlphabetSize, -1);
        for (size_t index = 0; index < s1.size(); ++index)
        {
            const char ch1 = s1[index];
            const char ch2 = s2[index];
            size_t parent1 = getParent(parents, ch1);
            size_t parent2 = getParent(parents, ch2);
            if (parent2 < parent1)
                std::swap(parent1, parent2);
            if (parent1 != parent2)
                parents[parent2] = static_cast<int>(parent1);
        }
        std::string result(baseStr);
        for (size_t index = 0; index < baseStr.size(); ++index)
        {
            result[index] = static_cast<char>(AlphabetStart + getParent(parents, baseStr[index]));
        }
        return result;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    [[nodiscard]] size_t getParent(std::vector<int> const &parents, char ch) const
    {
        size_t index = ch - AlphabetStart;
        while (parents[index] != -1)
            index = parents[index];
        return index;
    }
};

}

namespace LexSmallestEquivalentStringTask
{

TEST(LexSmallestEquivalentStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("makkek", solution.smallestEquivalentString("parker", "morris", "parser"));
    ASSERT_EQ("hdld", solution.smallestEquivalentString("hello", "world", "hold"));
    ASSERT_EQ("aauaaaaada", solution.smallestEquivalentString("leetcode", "programs", "sourcecode"));
}

}