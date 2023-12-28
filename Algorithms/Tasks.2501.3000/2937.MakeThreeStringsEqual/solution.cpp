#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findMinimumOperations(std::string const &s1, std::string const &s2, std::string const &s3) const
    {
        if ((s1.front() != s2.front()) || (s1.front() != s3.front()))
            return -1;
        const size_t minSize = std::min(s1.size(), std::min(s2.size(), s3.size()));
        std::string value1(s1, 0, minSize);
        std::string value2(s2, 0, minSize);
        std::string value3(s3, 0, minSize);
        while ((value1 != value2) || (value1 != value3))
        {
            value1.pop_back();
            value2.pop_back();
            value3.pop_back();
        }
        return static_cast<int>(s1.size() + s2.size() + s3.size() - value1.size() - value2.size() - value3.size());
    }
};

}

namespace MakeThreeStringsEqualTask
{

TEST(MakeThreeStringsEqualTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findMinimumOperations("abc", "abb", "ab"));
    ASSERT_EQ(-1, solution.findMinimumOperations("dac", "bac", "cac"));
}

}