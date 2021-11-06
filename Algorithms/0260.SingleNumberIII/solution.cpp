#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> singleNumber(std::vector<int> const &nums) const
    {
        // Let first & second - numbers, which appear only once
        // nums[0] ^ nums[1] ^ ... ^ nums[nums.size() - 1] = first ^ second
        int firstSecondXor = 0;
        for (const int num : nums)
            firstSecondXor ^= num;
        // Let find rightmost one bit. This bit sets in the first or second only, not in both.
        int rightmostBitMask = 1;
        while ((firstSecondXor & rightmostBitMask) == 0)
            rightmostBitMask <<= 1;
        // Let calculate xor value of numbers in which this bit sets in one.
        // This xor value equals first or second, obviously
        int first = 0;
        for (const int num : nums)
        {
            if ((num & rightmostBitMask) != 0)
                first ^= num;
        }
        return {first, firstSecondXor ^ first};
    }
};

}

namespace SingleNumberIIITask
{

TEST(SingleNumberIIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3, 5}), solution.singleNumber({1, 2, 1, 3, 2, 5}));
    ASSERT_EQ(std::vector<int>({-1, 0}), solution.singleNumber({-1, 0}));
    ASSERT_EQ(std::vector<int>({1, 0}), solution.singleNumber({0, 1}));
}

}