#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findBestValue(std::vector<int> const &arr, int target) const
    {
        std::vector<int> numbers(arr);
        std::sort(numbers.begin(), numbers.end());
        BestValue currentBestValue(0, target);
        int prefixSum = 0;
        for (size_t index = 0; index < numbers.size(); ++index)
        {
            const int prevNumber = index > 0 ? numbers[index - 1] : 0;
            const int restNumberCount = static_cast<int>(numbers.size() - index);
            if (prevNumber != numbers[index])
                currentBestValue = calcBestValue(currentBestValue, target, prefixSum, prevNumber, numbers[index], restNumberCount);
            prefixSum += numbers[index];
        }
        return currentBestValue.Value;
    }

private:
    struct BestValue
    {
        BestValue(int value, int delta) : Value(value), Delta(delta)
        {
        }

        int Value;
        int Delta;
    };

    [[nodiscard]] BestValue calcBestValue(BestValue const &currentBestValue, int target, int prefixSum, int prevNumber, int currentNumber, int restNumberCount) const
    {
        int bestValue = currentBestValue.Value;
        int bestDelta = currentBestValue.Delta;
        int currentValue = std::max(prevNumber, std::min(currentNumber, (target - prefixSum) / restNumberCount));
        int currentDelta = std::abs(prefixSum + currentValue * restNumberCount - target);
        if (currentDelta < bestDelta)
        {
            bestDelta = currentDelta;
            bestValue = currentValue;
        }
        if ((target - prefixSum) % restNumberCount == 0)
            return {bestValue, bestDelta};
        currentValue = std::max(prevNumber, std::min(currentNumber, 1 + (target - prefixSum) / restNumberCount));
        currentDelta = std::abs(prefixSum + currentValue * restNumberCount - target);
        if (currentDelta < bestDelta)
        {
            bestDelta = currentDelta;
            bestValue = currentValue;
        }
        return {bestValue, bestDelta};
    }
};

}

namespace SumOfMutatedArrayClosestToTargetTask
{

TEST(SumOfMutatedArrayClosestToTargetTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.findBestValue({4, 9, 3}, 10));
    ASSERT_EQ(5, solution.findBestValue({2, 3, 5}, 10));
    ASSERT_EQ(11361, solution.findBestValue({60864, 25176, 27249, 21296, 20204}, 56803));
}

TEST(SumOfMutatedArrayClosestToTargetTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(8175, solution.findBestValue({48772, 52931, 14253, 32289, 75263}, 40876));
}

}