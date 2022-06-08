#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int removePalindromeSub(std::string const &s) const
    {
        if (s.size() == 1)
            return 1;
        bool isPalindrome = true;
        bool hasA = false;
        bool hasB = false;
        for (size_t begin = 0, end = s.size() - 1; begin <= end; ++begin, --end)
        {
            isPalindrome &= (s[begin] == s[end]);
            hasA |= ((s[begin] == 'a') || (s[end] == 'a'));
            hasB |= ((s[begin] == 'b') || (s[end] == 'b'));
        }
        return (isPalindrome || !(hasA && hasB)) ? 1 : 2;
    }
};

}

namespace RemovePalindromicSubsequencesTask
{

TEST(RemovePalindromicSubsequencesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.removePalindromeSub("ababa"));
    ASSERT_EQ(2, solution.removePalindromeSub("abb"));
    ASSERT_EQ(2, solution.removePalindromeSub("baabb"));
}

}