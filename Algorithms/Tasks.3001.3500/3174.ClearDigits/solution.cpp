#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string clearDigits(std::string const &s) const
    {
        std::string result;
        result.reserve(s.size());
        for (const char ch : s)
        {
            if (std::isdigit(ch))
            {
                if (!result.empty())
                    result.pop_back();
            }
            else
                result.push_back(ch);
        }
        return result;
    }
};

}

namespace ClearDigitsTask
{

TEST(ClearDigitsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("abc", solution.clearDigits("abc"));
    ASSERT_EQ("", solution.clearDigits("cb34"));
}

}