#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSpecialEquivGroups(std::vector<std::string> const &words) const
    {
        std::unordered_set<std::string> groups;
        for (std::string const &word : words)
            groups.insert(createKey(word));
        return static_cast<int>(groups.size());
    }

private:
    [[nodiscard]] std::string createKey(std::string const &word) const
    {
        std::string key(word.size(), ' ');
        for (size_t index = 0, oddKeyIndex = 0, evenKeyIndex = word.size() / 2; index < word.size(); ++index)
            key[(index % 2 == 0 ? evenKeyIndex : oddKeyIndex)++] = word[index];
        // sort odd chars
        std::sort(key.begin(), std::next(key.begin(), static_cast<int>(word.size() / 2)));
        // sort even chars
        std::sort(std::next(key.begin(), static_cast<int>(word.size() / 2)), key.end());
        return key;
    }
};

}

namespace GroupsOfSpecialEquivalentStringsTask
{

TEST(GroupsOfSpecialEquivalentStringsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numSpecialEquivGroups({"abcd", "cdab", "cbad", "xyzz", "zzxy", "zzyx"}));
    ASSERT_EQ(3, solution.numSpecialEquivGroups({"abc", "acb", "bac", "bca", "cab", "cba"}));
}

}