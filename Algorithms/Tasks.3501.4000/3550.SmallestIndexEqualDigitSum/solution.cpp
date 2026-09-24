#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestIndex(std::vector<int> const &nums) const
    {
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const int digitSum = calcDigitSum(nums[index]);
            const int indexValue = static_cast<int>(index);
            if (digitSum == indexValue)
                return indexValue;
        }
        return -1;
    }

private:
    [[nodiscard]] int calcDigitSum(int number) const
    {
        int result = 0;
        for (; number != 0; number /= 10)
            result += (number % 10);
        return result;
    }
};

}

namespace SmallestIndexEqualDigitSumTask
{

TEST(SmallestIndexEqualDigitSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.smallestIndex({1, 3, 2}));
    ASSERT_EQ(1, solution.smallestIndex({1, 10, 11}));
    ASSERT_EQ(-1, solution.smallestIndex({1, 2, 3}));
}

}