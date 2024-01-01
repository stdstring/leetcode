#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int waysToMakeFair(std::vector<int> const &nums) const
    {
        std::vector<SumData> evenOddSums(nums.size(), SumData(0, 0));
        for (size_t rIndex = 0; rIndex < nums.size(); ++rIndex)
        {
            const size_t index = nums.size() - 1 - rIndex;
            evenOddSums[index].Even = nums[index] + (rIndex > 0 ? evenOddSums[index + 1].Odd : 0);
            evenOddSums[index].Odd = rIndex > 0 ? evenOddSums[index + 1].Even : 0;
        }
        size_t fairCount = 0;
        int prefixEvenSum = 0;
        int prefixOddSum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (index > 0)
            {
                const size_t prevIndex = index - 1;
                (prevIndex % 2 == 0 ? prefixEvenSum : prefixOddSum) += nums[prevIndex];
            }
            int evenSum = prefixEvenSum;
            int oddSum = prefixOddSum;
            if (index < (nums.size() - 1))
            {
                evenSum += (index % 2 == 0 ? evenOddSums[index + 1].Even : evenOddSums[index + 1].Odd);
                oddSum += (index % 2 == 1 ? evenOddSums[index + 1].Even : evenOddSums[index + 1].Odd);
            }
            if (evenSum == oddSum)
                ++fairCount;
        }
        return static_cast<int>(fairCount);
    }

private:
    struct SumData
    {
        SumData(int even, int odd) : Even(even), Odd(odd)
        {
        }
        int Even;
        int Odd;
    };
};

}

namespace WaysToMakeFairArrayTask
{

TEST(WaysToMakeFairArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.waysToMakeFair({2, 1, 6, 4}));
    ASSERT_EQ(3, solution.waysToMakeFair({1, 1, 1}));
    ASSERT_EQ(0, solution.waysToMakeFair({1, 2, 3}));
}

}