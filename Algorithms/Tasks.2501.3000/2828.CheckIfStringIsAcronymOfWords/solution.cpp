#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isAcronym(std::vector<std::string> const &words, std::string const &s) const
    {
        if (words.size() != s.size())
            return false;
        for (size_t index = 0; index < words.size(); ++index)
        {
            if (words[index].front() != s[index])
                return false;
        }
        return true;
    }
};

}

namespace CheckIfStringIsAcronymOfWordsTask
{

TEST(CheckIfStringIsAcronymOfWordsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isAcronym({"alice", "bob", "charlie"}, "abc"));
    ASSERT_EQ(false, solution.isAcronym({"an", "apple"}, "a"));
    ASSERT_EQ(true, solution.isAcronym({"never", "gonna", "give", "up", "on", "you"}, "ngguoy"));
}

}