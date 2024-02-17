#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestCombination(std::vector<int> const &candidates) const
    {
        constexpr int totalBitCount = 32;
        std::vector<int> bitsCount(totalBitCount, 0);
        for (const int number : candidates)
        {
            for (int bit = 0; bit < totalBitCount; ++bit)
            {
                const int mask = 1 << bit;
                if (mask > number)
                    break;
                if ((number & mask) > 0)
                    ++bitsCount[bit];
            }
        }
        return *std::ranges::max_element(bitsCount);
    }
};

}

namespace LargestCombinationBitwiseANDGreater0Task
{

TEST(LargestCombinationBitwiseANDGreater0TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.largestCombination({16, 17, 71, 62, 12, 24, 14}));
    ASSERT_EQ(2, solution.largestCombination({8, 8}));
}

}