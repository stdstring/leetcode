#include <string>
#include <stack>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string removeDuplicates(std::string const &s, int k) const
    {
        const size_t duplicatesCount = k;
        std::stack<std::pair<size_t, char>> charStack;
        for (char ch : s)
        {
            if (!charStack.empty() && (charStack.top().second == ch))
            {
                ++charStack.top().first;
                if (charStack.top().first == duplicatesCount)
                    charStack.pop();
            }
            else
                charStack.emplace(1, ch);
        }
        std::string result;
        while (!charStack.empty())
        {
            result.append(charStack.top().first, charStack.top().second);
            charStack.pop();
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

}

namespace RemoveAllAdjacentDuplicatesInStringIITask
{

TEST(RemoveAllAdjacentDuplicatesInStringIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("abcd", solution.removeDuplicates("abcd", 2));
    ASSERT_EQ("aa", solution.removeDuplicates("deeedbbcccbdaa", 3));
    ASSERT_EQ("ps", solution.removeDuplicates("pbbcggttciiippooaais", 2));
}

}