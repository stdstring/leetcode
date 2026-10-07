#include <algorithm>
#include <set>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> removeInvalidParentheses(std::string const &s) const
    {
        std::vector<size_t> parentheses;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if ((s[index] == '(') || (s[index] == ')'))
                parentheses.emplace_back(index);
        }
        if (parentheses.empty())
            return {s};
        const size_t remainingMaskBorder = 1ULL << parentheses.size();
        size_t bestRemaining = 0;
        std::vector<size_t> bestRemainingMasks({0});
        for (size_t remainingMask = 1; remainingMask < remainingMaskBorder; ++remainingMask)
        {
            size_t currentRemaining = calcOnesCount(remainingMask);
            if (currentRemaining < bestRemaining)
                continue;
            if (!checkRemainingParentheses(s, parentheses, remainingMask))
                continue;
            if (currentRemaining > bestRemaining)
                bestRemainingMasks.clear();
            bestRemaining = currentRemaining;
            bestRemainingMasks.emplace_back(remainingMask);
        }
        std::set<std::string> result;
        for (const size_t remainingMask : bestRemainingMasks)
        {
            result.emplace(generateRemainingParentheses(s, parentheses, remainingMask));
        }
        return {result.cbegin(), result.cend()};
    }

private:
    [[nodiscard]] size_t calcOnesCount(size_t number) const
    {
        size_t result = 0;
        for (; number > 0; number >>= 1)
        {
            if ((number & 1) != 0)
                ++result;
        }
        return result;
    }

    [[nodiscard]] bool checkRemainingParentheses(std::string const &s, std::vector<size_t> const &parentheses, size_t remainingMask) const
    {
        int balance = 0;
        int parenthesisMask = 1;
        for (const size_t index : parentheses)
        {
            if ((remainingMask & parenthesisMask) != 0)
            {
                balance += (s[index] == '(' ? 1 : -1);
                if (balance < 0)
                    return false;
            }
            parenthesisMask <<= 1;
        }
        return (balance == 0);
    }

    [[nodiscard]] std::string generateRemainingParentheses(std::string const &s, std::vector<size_t> const &parentheses, size_t remainingMask) const
    {
        std::string result;
        int parenthesisMask = 1;
        for (size_t index = 0, parenthesisIndex = 0; index < s.size(); ++index)
        {
            if ((parenthesisIndex < parentheses.size()) && (index == parentheses[parenthesisIndex]))
            {
                if ((remainingMask & parenthesisMask) != 0)
                    result.push_back(s[index]);
                ++parenthesisIndex;
                parenthesisMask <<= 1;
            }
            else
            {
                result.push_back(s[index]);
            }
        }
        return result;
    }
};

}

namespace RemoveInvalidParenthesesTask
{

TEST(RemoveInvalidParenthesesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"(())()", "()()()"}), solution.removeInvalidParentheses("()())()"));
    ASSERT_EQ(std::vector<std::string>({"(a())()","(a)()()"}), solution.removeInvalidParentheses("(a)())()"));
    ASSERT_EQ(std::vector<std::string>({""}), solution.removeInvalidParentheses(")("));
}

TEST(RemoveInvalidParenthesesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"n"}), solution.removeInvalidParentheses("n"));
    ASSERT_EQ(std::vector<std::string>({"f"}), solution.removeInvalidParentheses(")(f"));
}

}
