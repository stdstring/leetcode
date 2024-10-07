#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minLength(std::string const &s) const
    {
        std::string dest;
        for (char ch : s)
        {
            if ((ch == 'B') && !dest.empty() && (dest.back() == 'A'))
            {
                dest.pop_back();
                continue;
            }
            if ((ch == 'D') && !dest.empty() && (dest.back() == 'C'))
            {
                dest.pop_back();
                continue;
            }
            dest.push_back(ch);
        }
        return static_cast<int>(dest.size());
    }
};

}

namespace MinStringLengthAfterRemovingSubstringsTask
{

TEST(MinStringLengthAfterRemovingSubstringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minLength("ABFCACDB"));
    ASSERT_EQ(5, solution.minLength("ACBBD"));
}

}