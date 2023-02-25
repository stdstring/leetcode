#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minDominoRotations(std::vector<int> const &tops, std::vector<int> const &bottoms) const
    {
        constexpr size_t digitsCount = 6;
        std::vector<int> topRotations(digitsCount, 0);
        std::vector<int> bottomRotations(digitsCount, 0);
        size_t digitsRest = 6;
        for (size_t index = 0; index < tops.size(); ++index)
        {
            if (digitsRest == 0)
                return -1;
            const size_t topDigit = tops[index];
            const size_t bottomDigit = bottoms[index];
            for (size_t digit = 1; digit <= digitsCount; ++digit)
            {
                if (digit != topDigit && digit != bottomDigit)
                {
                    topRotations[digit - 1] = bottomRotations[digit - 1] = -1;
                    --digitsRest;
                }
                if (digit == topDigit && digit != bottomDigit && bottomRotations[digit - 1] != -1)
                    ++bottomRotations[digit - 1];
                if (digit != topDigit && digit == bottomDigit && topRotations[digit - 1] != -1)
                    ++topRotations[digit - 1];
            }
        }
        int minRotations = -1;
        for (size_t digit = 1; digit <= digitsCount; ++digit)
        {
            if (topRotations[digit - 1] != -1)
                minRotations = std::min(minRotations == -1 ? INT_MAX : minRotations, topRotations[digit - 1]);
            if (bottomRotations[digit - 1] != -1)
                minRotations = std::min(minRotations == -1 ? INT_MAX : minRotations, bottomRotations[digit - 1]);
        }
        return minRotations;
    }
};

}

namespace MinDominoRotationsForEqualRowTask
{

TEST(MinDominoRotationsForEqualRowTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.minDominoRotations({2, 1, 2, 4, 2, 2}, {5, 2, 6, 2, 3, 2}));
    ASSERT_EQ(-1, solution.minDominoRotations({3, 5, 1, 2, 3}, {3, 6, 3, 3, 4}));
}

}