#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string removeDuplicates(std::string const &s) const
    {
        std::string result;
        for (const char ch : s)
        {
            if (!result.empty() && result.back() == ch)
                result.pop_back();
            else
                result.push_back(ch);
        }
        return result;
    }
};

}

namespace RemoveAllAdjacentDuplicatesInStringTask
{

TEST(RemoveAllAdjacentDuplicatesInStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("ca", solution.removeDuplicates("abbaca"));
    ASSERT_EQ("ay", solution.removeDuplicates("azxxzy"));
}

}