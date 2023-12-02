#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumPartition(std::string const &s, int k) const
    {
        const long long maxValue = k;
        long long currentValue = 0;
        int partitionCount = 1;
        for (const char ch : s)
        {
            const int digit = ch - '0';
            currentValue = 10 * currentValue + digit;
            if (currentValue > maxValue)
            {
                if (maxValue < digit)
                    return -1;
                ++partitionCount;
                currentValue = digit;
            }
        }
        return partitionCount;
    }
};

}

namespace PartitionStringWithValuesAtMostKTask
{

TEST(PartitionStringWithValuesAtMostKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minimumPartition("165462", 60));
    ASSERT_EQ(-1, solution.minimumPartition("238182", 5));
}

TEST(PartitionStringWithValuesAtMostKTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumPartition("111", 1));
}

}