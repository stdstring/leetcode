#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> countBits(int num) const
    {
        std::vector<int> result;
        result.reserve(num + 1);
        result.push_back(0);
        int firstBit = 1;
        int firstBitMask = ~firstBit;
        int rangeMax = 1;
        for (int number = 1; number <= num; ++number)
        {
            if (number > rangeMax)
            {
                rangeMax = (rangeMax << 1) + 1;
                firstBit <<= 1;
                firstBitMask = ~firstBit;
            }
            result.push_back(1 + result[number & firstBitMask]);
        }
        return result;
    }
};

}

namespace CountingBitsTask
{

TEST(CountingBitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 1}), solution.countBits(2));
    ASSERT_EQ(std::vector<int>({0, 1, 1, 2, 1, 2}), solution.countBits(5));
}

}