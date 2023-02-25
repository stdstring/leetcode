#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string strWithout3a3b(int a, int b) const
    {
        std::string result;
        while ((a > 0) || (b > 0))
        {
            // empty
            if (result.empty())
                append(result, a > b ? 'a' : 'b', a > b ? a : b, a > b ? b : a);
            // last 'a'
            else if (result.back() == 'a')
                append(result, 'b', b, a);
            // last 'b'
            else
                append(result, 'a', a, b);
        }
        return result;
    }

private:
    void append(std::string &result, char ch, int &charRest, int otherRest) const
    {
        const int count = (charRest > otherRest) && (charRest > 1) ? 2 : 1;
        result.append(count, ch);
        charRest -= count;
    }
};

}

namespace StringWithoutAAAorBBBTask
{

TEST(StringWithoutAAAorBBBTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("bba", solution.strWithout3a3b(1, 2));
    ASSERT_EQ("aabaa", solution.strWithout3a3b(4, 1));
}

}