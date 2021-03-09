#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minInsertions(std::string const &s) const
    {
        int insertionCount = 0;
        int openBracketCount = 0;
        size_t pos = 0;
        while (pos < s.size())
        {
            const size_t nextPos = pos + 1;
            switch (s[pos])
            {
                case '(':
                    ++openBracketCount;
                    break;
                case ')':
                    if (nextPos < s.size() && s[nextPos] == ')')
                        pos = nextPos;
                    else
                        ++insertionCount;
                    --openBracketCount;
                    break;
                default: ;
            }
            if (openBracketCount == -1)
            {
                openBracketCount = 0;
                ++insertionCount;
            }
            ++pos;
        }
        return insertionCount + 2 * openBracketCount;
    }
};

}

namespace MinimumInsertionsToBalanceParenthesesStringTask
{

TEST(MinimumInsertionsToBalanceParenthesesStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minInsertions("(()))"));
    ASSERT_EQ(0, solution.minInsertions("())"));
    ASSERT_EQ(3, solution.minInsertions("))())("));
    ASSERT_EQ(12, solution.minInsertions("(((((("));
    ASSERT_EQ(5, solution.minInsertions(")))))))"));
}

}