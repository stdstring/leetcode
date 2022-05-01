#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool backspaceCompare(std::string const &s, std::string const &t) const
    {
        auto sIterator = s.crbegin();
        auto tIterator = t.crbegin();
        while ((sIterator != s.crend()) && (tIterator != t.crend()))
        {
            if ((*sIterator != BackspaceChar) && (*tIterator != BackspaceChar))
            {
                if (*sIterator != *tIterator)
                    return false;
                ++sIterator;
                ++tIterator;
            }
            else
            {
                sIterator = processBackspaces(sIterator, s.crend());
                tIterator = processBackspaces(tIterator, t.crend());
            }
        }
        if (sIterator != s.crend())
            sIterator = processBackspaces(sIterator, s.crend());
        if (tIterator != t.crend())
            tIterator = processBackspaces(tIterator, t.crend());
        return (sIterator == s.crend()) && (tIterator == t.crend());
    }

private:
    static constexpr char BackspaceChar = '#';

    [[nodiscard]] std::string::const_reverse_iterator processBackspaces(std::string::const_reverse_iterator iterator, std::string::const_reverse_iterator end) const
    {
        if (*iterator != BackspaceChar)
            return iterator;
        ++iterator;
        int balance = -1;
        while ((iterator != end) && (balance <= 0))
        {
            balance += (*iterator == BackspaceChar ? -1 : 1);
            ++iterator;
        }
        if (balance > 0)
            --iterator;
        return iterator;
    }
};

}

namespace BackspaceStringCompareTask
{

TEST(BackspaceStringCompareTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.backspaceCompare("ab#c", "ad#c"));
    ASSERT_EQ(true, solution.backspaceCompare("ab##", "c#d#"));
    ASSERT_EQ(false, solution.backspaceCompare("a#c", "b"));
}

TEST(BackspaceStringCompareTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.backspaceCompare("nzp#o#g", "b#nzp#o#g"));
    ASSERT_EQ(true, solution.backspaceCompare("xywrrmp", "xywrrmu#p"));
}


}