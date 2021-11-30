#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfArithmeticSlices(std::vector<int> const &nums) const
    {
        size_t count = 0;
        size_t start = 0;
        for (size_t index = 2; index < nums.size(); ++index)
        {
            const int currentDelta = nums[index] - nums[index - 1];
            const int startDelta = nums[start + 1] - nums[start];
            if (currentDelta != startDelta)
            {
                count += calcSubarrayCount(start, index - 1);
                start = index - 1;
            }
        }
        count += calcSubarrayCount(start, nums.size() - 1);
        return static_cast<int>(count);
    }

private:
    [[nodiscard]] size_t calcSubarrayCount(size_t start, size_t finish) const
    {
        // (size - 2) (count of arrays of size 3) + (size - 3) (count of arrays of size 4) + ... = (size - 2) * (size - 1) / 2
        const size_t size = finish - start + 1;
        return (size - 2) * (size - 1) / 2;
    }
};

}

namespace ArithmeticSlicesTask
{

TEST(ArithmeticSlicesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numberOfArithmeticSlices({1, 2, 3, 4}));
    ASSERT_EQ(0, solution.numberOfArithmeticSlices({1}));
}

}