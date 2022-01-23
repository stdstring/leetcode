#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> sequentialDigits(int low, int high) const
    {
        const std::vector<int> possibleNumbers({12, 23, 34, 45, 56, 67, 78, 89,
                                                123, 234, 345, 456, 567, 678, 789,
                                                1234, 2345, 3456, 4567, 5678, 6789,
                                                12345, 23456, 34567, 45678, 56789,
                                                123456, 234567, 345678, 456789,
                                                1234567, 2345678, 3456789,
                                                12345678, 23456789,
                                                123456789});
        const auto lowerBound = std::lower_bound(possibleNumbers.cbegin(), possibleNumbers.cend(), low);
        const auto upperBound = std::upper_bound(possibleNumbers.cbegin(), possibleNumbers.cend(), high);
        std::vector<int> result(lowerBound, upperBound);
        return result;
    }
};

}

namespace SequentialDigitsTask
{

TEST(SequentialDigitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({123, 234}), solution.sequentialDigits(100, 300));
    ASSERT_EQ(std::vector<int>({1234, 2345, 3456, 4567, 5678, 6789, 12345}), solution.sequentialDigits(1000, 13000));
}

}