#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumLength(std::string const &s) const
    {
        size_t begin = 0;
        size_t end = s.size() - 1;
        while (begin < end)
        {
            if (s[begin] != s[end])
                break;
            const char ch = s[begin];
            for (; (begin <= end) && (s[begin] == ch); ++begin) {}
            for (; (begin <= end) && (s[end] == ch); --end) {}
        }
        if (begin > end)
            return 0;
        return static_cast<int>(end - begin + 1);
    }
};

}

namespace MinLengthAfterDeletingSimilarEndsTask
{

TEST(MinLengthAfterDeletingSimilarEndsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumLength("ca"));
    ASSERT_EQ(0, solution.minimumLength("cabaabac"));
    ASSERT_EQ(3, solution.minimumLength("aabccabba"));
}

}