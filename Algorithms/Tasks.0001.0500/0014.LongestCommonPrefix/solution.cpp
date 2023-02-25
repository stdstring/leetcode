#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string longestCommonPrefix(std::vector<std::string> const &strs)
    {
        if (strs.empty())
            return "";
        std::string dest;
        size_t index = 0;
        while (checkIndex(strs, index))
        {
            dest.push_back(strs[0][index]);
            ++index;
        }
        return dest;
    }

private:
    bool checkIndex(std::vector<std::string> const& strs, size_t index)
    {
        if (strs[0].size() <= index)
            return false;
        const char expectedChar = strs[0][index];
        for(std::string const &str : strs)
        {
            if (str.size() <= index)
                return false;
            if (expectedChar != str[index])
                return false;
        }
        return expectedChar != 0;
    }
};

}

namespace LongestCommonPrefixTask
{

TEST(LongestCommonPrefixTaskTests, Examples)
{
    Solution solution;
    ASSERT_EQ("fl", solution.longestCommonPrefix({"flower", "flow", "flight"}));
    ASSERT_EQ("", solution.longestCommonPrefix({"dog", "racecar", "car"}));
}

TEST(LongestCommonPrefixTaskTests, FromWrongAnswers)
{
    Solution solution;
    ASSERT_EQ("", solution.longestCommonPrefix({}));
}

}