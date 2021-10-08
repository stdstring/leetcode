#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string reverseParentheses(std::string const &s) const
    {
        std::string result;
        for (size_t index = 0; index < s.size();)
        {
            if (s[index] == '(')
                result.append(reverseImpl(s, index));
            else
                result.push_back(s[index++]);
        }
        return result;
    }

private:
    std::string reverseImpl(std::string const &source, size_t &index) const
    {
        // process '('
        ++index;
        std::string dest;
        while (source[index] != ')')
        {
            if (source[index] == '(')
                dest.append(reverseImpl(source, index));
            else
                dest.push_back(source[index++]);
        }
        // process ')'
        ++index;
        return {dest.crbegin(), dest.crend()};
    }
};

}

namespace RevSubstrBetweenEachPairOfParenthesesTask
{

TEST(RevSubstrBetweenEachPairOfParenthesesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("dcba", solution.reverseParentheses("(abcd)"));
    ASSERT_EQ("iloveu", solution.reverseParentheses("(u(love)i)"));
    ASSERT_EQ("leetcode", solution.reverseParentheses("(ed(et(oc))el)"));
    ASSERT_EQ("apmnolkjihgfedcbq", solution.reverseParentheses("a(bcdefghijkl(mno)p)q"));
}

}