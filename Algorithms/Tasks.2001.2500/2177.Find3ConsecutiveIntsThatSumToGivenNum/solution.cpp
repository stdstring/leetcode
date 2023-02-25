#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> sumOfThree(long long num) const
    {
        if (num % 3 == 0)
            return {num / 3 - 1, num / 3, num / 3 + 1};
        return {};
    }
};

}

namespace Find3ConsecutiveIntsThatSumToGivenNumTask
{

TEST(Find3ConsecutiveIntsThatSumToGivenNumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<long long>({10, 11, 12}), solution.sumOfThree(33));
    ASSERT_EQ(std::vector<long long>(), solution.sumOfThree(4));
}

}
