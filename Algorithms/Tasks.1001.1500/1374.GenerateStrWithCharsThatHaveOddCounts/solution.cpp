#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string generateTheString(int n) const
    {
        const size_t count = n;
        return n % 2 == 1 ? std::string(count, 'x') : std::string(count - 1, 'x').append("y");
    }
};

}

namespace GenerateStrWithCharsThatHaveOddCountsTask
{

TEST(GenerateStrWithCharsThatHaveOddCountsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("xxxy", solution.generateTheString(4));
    ASSERT_EQ("xy", solution.generateTheString(2));
    ASSERT_EQ("xxxxxxx", solution.generateTheString(7));
}

}