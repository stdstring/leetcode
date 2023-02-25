#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isInterleave(std::string const &s1, std::string const &s2, std::string const &s3) const
    {
        if (s3.size() != (s1.size() + s2.size()))
            return false;
        std::vector<bool> prev(s2.size() + 1, false);
        std::vector<bool> current(s2.size() + 1, false);
        current[0] = true;
        for (size_t i = 0; i < s1.size() + 1; ++i)
        {
            for (size_t j = 0; j < s2.size() + 1; ++j)
            {
                if ((i == 0) && (j == 0))
                    continue;
                current[j] = false;
                if (i > 0)
                    current[j] = current[j] || (prev[j] && (s3[j + i - 1] == s1[i - 1]));
                if (j > 0)
                    current[j] = current[j] || (current[j - 1] && (s3[i + j - 1] == s2[j - 1]));
            }
            std::swap(prev, current);
        }
        return prev.back();
    }
};

}

namespace InterleavingStringTask
{

TEST(InterleavingStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isInterleave("aabcc", "dbbca", "aadbbcbcac"));
    ASSERT_EQ(false, solution.isInterleave("aabcc", "dbbca", "aadbbbaccc"));
    ASSERT_EQ(true, solution.isInterleave("", "", ""));
}

TEST(InterleavingStringTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isInterleave("", "", "a"));
}

}