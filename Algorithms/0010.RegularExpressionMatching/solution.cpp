#include <stack>
#include <string>

#include "gtest/gtest.h"

namespace
{

class State
{
public:
    State(size_t patternStart, size_t matchStart, size_t matchSize) :
        patternStart(patternStart),
        matchStart(matchStart),
        matchSize(matchSize)
    {
    }

    size_t patternStart;
    size_t matchStart;
    size_t matchSize;
};

enum Action { NEXT, REVERT };

class Solution
{
public:
    bool isMatch(std::string const &s, std::string const &p) const
    {
        if (p.empty())
            return s.empty();
        std::stack<State> stateStack;
        size_t sourceIndex = 0;
        size_t patternIndex = 0;
        Action action = Action::NEXT;
        while (sourceIndex < s.size())
        {
            if (patternIndex == p.size())
            {
                action = Action::REVERT;
                patternIndex = 0;
                continue;
            }
            switch (action)
            {
            case Action::NEXT:
                if (isSingleCharPattern(p, patternIndex))
                {
                    if (p[patternIndex] == '.' || s[sourceIndex] == p[patternIndex])
                    {
                        ++sourceIndex;
                        ++patternIndex;
                    }
                    else
                        action = Action::REVERT;
                }
                else
                {
                    stateStack.emplace(patternIndex, sourceIndex, 0);
                    patternIndex += 2;
                }
                break;
            case Action::REVERT:
                if (stateStack.empty())
                    return false;
                State currentState = stateStack.top();
                stateStack.pop();
                if (p[currentState.patternStart] == '.' || s[currentState.matchStart + currentState.matchSize] == p[currentState.patternStart])
                {
                    currentState.matchSize += 1;
                    stateStack.push(currentState);
                    patternIndex = currentState.patternStart + 2;
                    sourceIndex = currentState.matchStart + currentState.matchSize;
                    action = Action::NEXT;
                }
                break;
            }
        }
        return canMatchEndOfSource(p, patternIndex);
    }

private:
    bool isSingleCharPattern(std::string const &pattern, size_t patternIndex) const
    {
        return patternIndex == (pattern.size() - 1) || pattern[patternIndex + 1] != '*';
    }

    bool canMatchEndOfSource(std::string const &pattern, size_t patternIndex) const
    {
        while (patternIndex < pattern.size())
        {
            if ((patternIndex + 1) == pattern.size() || pattern[patternIndex + 1] != '*')
                return false;
            patternIndex += 2;
        }
        return true;
    }
};

}

namespace RegularExpressionMatchingTask
{

TEST(RegularExpressionMatchingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isMatch("aa", "a"));
    ASSERT_EQ(true, solution.isMatch("aa", "a*"));
    ASSERT_EQ(true, solution.isMatch("ab", ".*"));
    ASSERT_EQ(true, solution.isMatch("aab", "c*a*b"));
    ASSERT_EQ(false, solution.isMatch("mississippi", "mis*is*p*."));
}

TEST(RegularExpressionMatchingTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isMatch("a", ""));
}

}
