#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> maximumBobPoints(int numArrows, std::vector<int> const &aliceArrows) const
    {
        const int bitCount = static_cast<int>(aliceArrows.size());
        const int maxMaskValue = 1 << bitCount;
        int bestBobPoints = 0;
        std::vector<int> bestBobArrows;
        for (int bobMask = 1; bobMask < maxMaskValue; ++bobMask)
        {
            auto const &[currentBobPoints, currentBobArrows] = calcBobPoints(bobMask, numArrows, aliceArrows);
            if (currentBobPoints > bestBobPoints)
            {
                bestBobPoints = currentBobPoints;
                bestBobArrows = currentBobArrows;
            }
        }
        return bestBobArrows;
    }

private:
    [[nodiscard]] std::pair<int, std::vector<int>> calcBobPoints(int bobMask, int numArrows, std::vector<int> const &aliceArrows) const
    {
        const int bitCount = static_cast<int>(aliceArrows.size());
        int bobPoints = 0;
        std::vector<int> bobArrows(aliceArrows.size(), 0);
        for (int bit = bitCount - 1; bit >= 0; --bit)
        {
            const int currentMask = 1 << bit;
            if ((bobMask & currentMask) != 0)
            {
                bobArrows[bit] = std::min(numArrows, aliceArrows[bit] + 1);
                numArrows -= bobArrows[bit];
                bobPoints += (bobArrows[bit] > aliceArrows[bit] ? bit : 0);
            }
            if (numArrows == 0)
                break;
        }
        if (numArrows > 0)
            bobArrows[0] += numArrows;
        return {bobPoints, bobArrows};
    }
};

}

namespace MaxPointsInArcheryCompetitionTask
{

TEST(MaxPointsInArcheryCompetitionTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 0, 0, 0, 1, 1, 0, 0, 1, 2, 3, 1}), solution.maximumBobPoints(9, {1, 1, 0, 1, 0, 0, 2, 1, 0, 1, 2, 0}));
    ASSERT_EQ(std::vector<int>({0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}), solution.maximumBobPoints(3, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2}));
}

TEST(MaxPointsInArcheryCompetitionTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({21, 3, 0, 2, 8, 2, 17, 8, 4, 14, 4, 6}), solution.maximumBobPoints(89, {3, 2, 28, 1, 7, 1, 16, 7, 3, 13, 3, 5}));
}

}