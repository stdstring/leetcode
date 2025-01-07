#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> stringMatching(std::vector<std::string> const &words) const
    {
        std::vector<std::string> result;
        for (size_t current = 0; current < words.size(); ++current)
        {
            for (size_t other = 0; other < words.size(); ++other)
            {
                if (current == other)
                    continue;
                if (words[current].size() > words[other].size())
                    continue;
                if (words[other].find(words[current]) != std::string::npos)
                {
                    result.emplace_back(words[current]);
                    break;
                }
            }
        }
        return result;
    }
};

}

namespace StringMatchingInArrayTask
{

TEST(StringMatchingInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"as", "hero"}), solution.stringMatching({"mass", "as", "hero", "superhero"}));
    ASSERT_EQ(std::vector<std::string>({"et", "code"}), solution.stringMatching({"leetcode", "et", "code"}));
    ASSERT_EQ(std::vector<std::string>(), solution.stringMatching({"blue", "green", "bu"}));
}

}