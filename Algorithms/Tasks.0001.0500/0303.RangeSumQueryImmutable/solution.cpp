#include <vector>

#include "gtest/gtest.h"

namespace
{

class NumArray
{
public:
    NumArray(std::vector<int> const &nums)
    {
        for (int number : nums)
        {
            _prefixSums.push_back(number + (_prefixSums.empty() ? 0 : _prefixSums.back()));
        }
    }

    int sumRange(int i, int j)
    {
        const int prefixSumFrom = (i == 0 ? 0 : _prefixSums[i - 1]);
        const int prefixSumTo = _prefixSums[j];
        return prefixSumTo - prefixSumFrom;
    }

private:
    std::vector<int> _prefixSums;
};

}

namespace RangeSumQueryImmutableTask
{

TEST(RangeSumQueryImmutableTaskTests, Examples)
{
    NumArray numArray({-2, 0, 3, -5, 2, -1});
    ASSERT_EQ(1, numArray.sumRange(0, 2));
    ASSERT_EQ(-1, numArray.sumRange(2, 5));
    ASSERT_EQ(-3, numArray.sumRange(0, 5));
}

}