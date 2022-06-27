#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minPartitions(std::string const &n) const
    {
        return *std::max_element(n.cbegin(), n.cend()) - '0';
    }
};

}

namespace PartitioningIntoMinNumOfDeciBinaryNumsTask
{

TEST(PartitioningIntoMinNumOfDeciBinaryNumsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minPartitions("32"));
    ASSERT_EQ(8, solution.minPartitions("82734"));
    ASSERT_EQ(9, solution.minPartitions("27346209830709182346"));
}

}