#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findLUSlength(std::vector<std::string> const &strs) const
    {
        std::vector<std::string> strings(strs);
        std::sort(strings.begin(), strings.end(), [](std::string const &l, std::string const &r){ return l.size() < r.size(); });
        std::vector<bool> processed(strings.size(), false);
        std::string result;
        for (size_t from = 0; from < strings.size(); ++from)
        {
            if (processed[from])
                continue;
            processed[from] = true;
            bool uncommonSubsequence = true;
            for (size_t to = from + 1; to < strings.size(); ++to)
            {
                if (!isUncommonSubsequence(strings[from], strings[to]))
                {
                    uncommonSubsequence = false;
                    processed[to] = strings[from].size() == strings[to].size();
                }
            }
            if (uncommonSubsequence)
                result = strings[from];
        }
        return result.empty() ? -1 : static_cast<int>(result.size());
    }

private:
    [[nodiscard]] bool isUncommonSubsequence(std::string const &fromStr, std::string const &toStr) const
    {
        size_t fromIndex = 0;
        for (const char ch : toStr)
        {
            if (fromStr[fromIndex] == ch)
                ++fromIndex;
            if (fromIndex == fromStr.size())
                return false;
        }
        return true;
    }
};

}

namespace LongestUncommonSubsequenceIITaskTest
{

TEST(LongestUncommonSubsequenceIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.findLUSlength({"aba", "cdc", "eae"}));
    ASSERT_EQ(-1, solution.findLUSlength({"aaa", "aaa", "aa"}));
}

TEST(LongestUncommonSubsequenceIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findLUSlength({"aabbcc", "aabbcc", "cb"}));
    ASSERT_EQ(2, solution.findLUSlength({"aabbcc", "aabbcc", "cb", "abc"}));
    ASSERT_EQ(6, solution.findLUSlength({"aabbcc", "aabbcc", "c", "e", "aabbcd"}));
}

}