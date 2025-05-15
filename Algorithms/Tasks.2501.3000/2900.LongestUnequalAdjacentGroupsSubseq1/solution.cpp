#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> getLongestSubsequence(std::vector<std::string> const &words, std::vector<int> const &groups) const
    {
        std::vector<std::string> result;
        result.emplace_back(words[0]);
        int currentGroup = groups[0];
        for (size_t index = 1; index < words.size(); ++index)
        {
            if (currentGroup != groups[index])
            {
                result.emplace_back(words[index]);
                currentGroup = groups[index];
            }
        }
        return result;
    }
};

}

namespace LongestUnequalAdjacentGroupsSubseq1Task
{

TEST(LongestUnequalAdjacentGroupsSubseq1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"e", "b"}), solution.getLongestSubsequence({"e", "a", "b"}, {0, 0, 1}));
    ASSERT_EQ(std::vector<std::string>({"a", "b", "c"}), solution.getLongestSubsequence({"a", "b", "c", "d"}, {1, 0, 1, 1}));
}

}