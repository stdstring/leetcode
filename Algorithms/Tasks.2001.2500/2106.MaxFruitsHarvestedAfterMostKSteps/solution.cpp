#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxTotalFruits(std::vector<std::vector<int>> const& fruits, int startPos, int k) const
    {
        return std::max(moveLeft(fruits, startPos, k), moveRight(fruits, startPos, k));
    }

private:
    [[nodiscard]] int moveLeft(std::vector<std::vector<int>> const &fruits, int startPos, int k) const
    {
        if (startPos > fruits.back()[0])
            return 0;
        if ((startPos + k) < fruits.front()[0])
            return 0;
        const size_t lastIndex = fruits.size() - 1;
        // prepare sliding window
        size_t startRIndex = 0;
        for (; (startRIndex < fruits.size()) && ((fruits[lastIndex - startRIndex][0] - k) > startPos); ++startRIndex) {}
        size_t endRIndex = startRIndex;
        int currentResult = 0;
        for (; (endRIndex < fruits.size()) && (fruits[lastIndex - endRIndex][0] >= startPos); ++endRIndex)
            currentResult += fruits[lastIndex - endRIndex][1];
        int bestResult = currentResult;
        // move sliding window
        for (; endRIndex < fruits.size(); ++endRIndex)
        {
            if (2 * (startPos - fruits[lastIndex - endRIndex][0]) > k)
                break;
            for (; (fruits[lastIndex - startRIndex][0] > startPos); ++startRIndex)
            {
                const int currentDistance = 2 * (startPos - fruits[lastIndex - endRIndex][0]) + (fruits[lastIndex - startRIndex][0] - startPos);
                if (currentDistance <= k)
                    break;
                currentResult -= fruits[lastIndex - startRIndex][1];
            }
            if (fruits[lastIndex - startRIndex][0] <= startPos)
                break;
            currentResult += fruits[lastIndex - endRIndex][1];
            bestResult = std::max(bestResult, currentResult);
        }
        return bestResult;
    }

    [[nodiscard]] int moveRight(std::vector<std::vector<int>> const &fruits, int startPos, int k) const
    {
        if (startPos < fruits.front()[0])
            return 0;
        if ((startPos - k) > fruits.back()[0])
            return 0;
        // prepare sliding window
        size_t startIndex = 0;
        for (; (startIndex < fruits.size()) && ((fruits[startIndex][0] + k) < startPos); ++startIndex) {}
        size_t endIndex = startIndex;
        int currentResult = 0;
        for (; (endIndex < fruits.size()) && (fruits[endIndex][0] <= startPos); ++endIndex)
            currentResult += fruits[endIndex][1];
        int bestResult = currentResult;
        // move sliding window
        for(; endIndex < fruits.size(); ++endIndex)
        {
            if (2 * (fruits[endIndex][0] - startPos) > k)
                break;
            for (;(fruits[startIndex][0] < startPos) ; ++startIndex)
            {
                const int currentDistance = 2 * (fruits[endIndex][0] - startPos) + (startPos - fruits[startIndex][0]);
                if (currentDistance <= k)
                    break;
                currentResult -= fruits[startIndex][1];
            }
            if (fruits[startIndex][0] >= startPos)
                break;
            currentResult += fruits[endIndex][1];
            bestResult = std::max(bestResult, currentResult);
        }
        return bestResult;
    }
};

}

namespace MaxFruitsHarvestedAfterMostKStepsTask
{

TEST(MaxFruitsHarvestedAfterMostKStepsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.maxTotalFruits({{2, 8}, {6, 3}, {8, 6}}, 5, 4));
    ASSERT_EQ(14, solution.maxTotalFruits({{0, 9}, {4, 1}, {5, 7}, {6, 2}, {7, 4}, {10, 9}}, 5, 4));
    ASSERT_EQ(0, solution.maxTotalFruits({{0, 3}, {6, 4}, {8, 5}}, 3, 2));
}

TEST(MaxFruitsHarvestedAfterMostKStepsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(10000, solution.maxTotalFruits({{200000, 10000}}, 0, 200000));
    ASSERT_EQ(38, solution.maxTotalFruits({{5, 8}, {7, 7}, {8, 7}, {15, 5}, {18, 8}, {19, 3}, {25, 4}, {26, 1}, {34, 10}, {38, 3}, {39, 4}, {40, 5}}, 6, 19));
}

}