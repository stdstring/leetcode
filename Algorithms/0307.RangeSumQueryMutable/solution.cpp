#include <vector>

#include "gtest/gtest.h"

namespace
{

class NumArray
{
public:
    NumArray(std::vector<int> const &nums) : _tree(nums.size(), 0)
    {
        for (size_t index = 0; index < nums.size(); ++index)
            add(static_cast<int>(index + 1), nums[index]);
    }

    void update(int i, int val)
    {
        const int number = sumRange(i, i);
        add(i + 1, val - number);
    }

    int sumRange(int i, int j)
    {
        return sum(j + 1) - sum(i);
    }

private:
    std::vector<int> _tree;

    int sum(int k)
    {
        int sum = 0;
        while (k >= 1)
        {
            sum += _tree[static_cast<size_t>(k) - 1];
            const int pk = k & (-k);
            k -= pk;
        }
        return sum;
    }

    void add(int k, int val)
    {
        while (static_cast<size_t>(k) <= _tree.size())
        {
            _tree[static_cast<size_t>(k) - 1] += val;
            const int pk = k & (-k);
            k += pk;
        }
    }
};

}

namespace RangeSumQueryMutableTask
{

TEST(RangeSumQueryMutableTaskTests, Examples)
{
    NumArray numArray({1, 3, 5});
    ASSERT_EQ(9, numArray.sumRange(0, 2));
    ASSERT_NO_THROW(numArray.update(1, 2));
    ASSERT_EQ(8, numArray.sumRange(0, 2));
}

}