#include <algorithm>
#include <string>
#include <unordered_set>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxUniqueSplit(std::string const &s) const
    {
        std::unordered_set<std::string> knownWords;
        return static_cast<int>(calcMaxUniqueSplit(s, 0, knownWords));
    }

private:
    [[nodiscard]] size_t calcMaxUniqueSplit(std::string const &s, size_t start, std::unordered_set<std::string> &knownWords) const
    {
        if (start == s.size())
            return knownWords.size();
        size_t maxSplitCount = 1;
        std::string currentWord;
        for (size_t current = start; (current < s.size()) && (knownWords.size() + s.size() - current > maxSplitCount); ++current)
        {
            currentWord.push_back(s[current]);
            if (knownWords.count(currentWord) != 0)
                continue;
            knownWords.insert(currentWord);
            maxSplitCount = std::max(maxSplitCount, calcMaxUniqueSplit(s, current + 1, knownWords));
            knownWords.erase(currentWord);
        }
        return maxSplitCount;
    }
};

}

namespace SplitStringIntoMaxUniqueSubstringsTask
{

TEST(SplitStringIntoMaxUniqueSubstringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maxUniqueSplit("ababccc"));
    ASSERT_EQ(2, solution.maxUniqueSplit("aba"));
    ASSERT_EQ(1, solution.maxUniqueSplit("aa"));
}

}