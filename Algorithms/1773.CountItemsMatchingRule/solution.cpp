#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countMatches(std::vector<std::vector<std::string>> const &items, std::string const &ruleKey, std::string const &ruleValue) const
    {
        size_t matches = 0;
        for (std::vector<std::string> const &item : items)
        {
            if (isMatch(item, ruleKey, ruleValue))
                ++matches;
        }
        return static_cast<int>(matches);
    }

private:
    bool isMatch(std::vector<std::string> const &item, std::string const &ruleKey, std::string const &ruleValue) const
    {
        const size_t typeIndex = 0;
        const size_t colorIndex = 1;
        const size_t nameIndex = 2;
        if (ruleKey == "type")
            return item[typeIndex] == ruleValue;
        if (ruleKey == "color")
            return item[colorIndex] == ruleValue;
        if (ruleKey == "name")
            return item[nameIndex] == ruleValue;
        return false;
    }
};

}

namespace CountItemsMatchingRuleTask
{

TEST(CountItemsMatchingRuleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.countMatches({{"phone", "blue", "pixel"}, {"computer", "silver", "lenovo"}, {"phone", "gold", "iphone"}}, "color", "silver"));
    ASSERT_EQ(2, solution.countMatches({{"phone", "blue", "pixel"}, {"computer", "silver", "phone"}, {"phone", "gold", "iphone"}}, "type", "phone"));
}

}