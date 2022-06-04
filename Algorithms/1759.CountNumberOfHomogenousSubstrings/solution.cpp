#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countHomogenous(std::string const &s) const
    {
        constexpr unsigned long long modValue = 1000000007;
        size_t start = 0;
        unsigned long long count = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] != s[start])
            {
                count += calcSubstringCount(index - start);
                start = index;
            }
        }
        count += calcSubstringCount(s.size() - start);
        return static_cast<int>(count % modValue);
    }

private:
    [[nodiscard]] unsigned  long long calcSubstringCount(unsigned long long size) const
    {
        return (1 + size) * size / 2;
    }
};

}

namespace CountNumberOfHomogenousSubstringsTask
{

TEST(CountNumberOfHomogenousSubstringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.countHomogenous("abbcccaa"));
    ASSERT_EQ(2, solution.countHomogenous("xy"));
    ASSERT_EQ(15, solution.countHomogenous("zzzzz"));
}

}