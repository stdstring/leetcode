#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool rotateString(std::string const &a, std::string const &b) const
    {
        if (a.size() != b.size())
            return false;
        if (a.empty())
            return true;
        size_t firstCharIndex = b.find(a[0]);
        while (firstCharIndex != std::string::npos)
        {
            if (compareStrings(a, b, firstCharIndex))
                return true;
            firstCharIndex = b.find(a[0], firstCharIndex + 1);
        }
        return false;
    }

private:
    bool compareStrings(std::string const &source, std::string const &dest, size_t firstCharIndex) const
    {
        if (source.compare(0, source.size() - firstCharIndex, dest, firstCharIndex) != 0)
            return false;
        return (firstCharIndex == 0) || (source.compare(source.size() - firstCharIndex, firstCharIndex, dest, 0, firstCharIndex) == 0);
    }
};

}

namespace RotateStringTask
{

TEST(RotateStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.rotateString("abcde", "cdeab"));
    ASSERT_EQ(false, solution.rotateString("abcde", "abced"));
}

TEST(RotateStringTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.rotateString("", ""));
}

}