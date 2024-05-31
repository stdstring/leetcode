#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkPalindromeFormation(std::string const &a, std::string const &b) const
    {
        return isPalindrome(a, b) || isPalindrome(b, a);
    }

private:
    [[nodiscard]] bool isPalindrome(std::string const &a, std::string const &b) const
    {
        size_t start = 0;
        size_t end = a.size() - 1;
        for (; start < end; ++start, --end)
        {
            if (a[start] != b[end])
                break;
        }
        if (end <= start)
            return true;
        return isPalindrome(a, start, end) || isPalindrome(b, start, end);
    }

    [[nodiscard]] bool isPalindrome(std::string const &s, size_t start, size_t end) const
    {
        for(;start < end; ++start, --end)
        {
            if (s[start] != s[end])
                return false;
        }
        return true;
    }
};

}

namespace SplitTwoStringsMakePalindromeTask
{

TEST(SplitTwoStringsMakePalindromeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkPalindromeFormation("x", "y"));
    ASSERT_EQ(false, solution.checkPalindromeFormation("xbdef", "xecab"));
    ASSERT_EQ(true, solution.checkPalindromeFormation("ulacfd", "jizalu"));
}

}