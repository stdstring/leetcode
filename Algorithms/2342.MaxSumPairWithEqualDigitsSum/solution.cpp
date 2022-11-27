#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumSum(std::vector<int> const &nums) const
    {
        constexpr size_t maxDigitCount = 9;
        constexpr size_t maxDigitSum = maxDigitCount * 9;
        std::vector<std::vector<int>> bestNumbers(maxDigitSum + 1, std::vector<int>());
        for (int number : nums)
        {
            const int digitSum = calcDigitSum(number);
            if (bestNumbers[digitSum].size() < 2)
                bestNumbers[digitSum].push_back(number);
            else if ((number >= bestNumbers[digitSum][0]) && (number >= bestNumbers[digitSum][1]))
            {
                const int bestNumber = std::max(bestNumbers[digitSum][0], bestNumbers[digitSum][1]);
                bestNumbers[digitSum][0] = number;
                bestNumbers[digitSum][1] = bestNumber;
            }
            else if ((number >= bestNumbers[digitSum][0]) && (number < bestNumbers[digitSum][1]))
                bestNumbers[digitSum][0] = number;
            else if ((number < bestNumbers[digitSum][0]) && (number >= bestNumbers[digitSum][1]))
                bestNumbers[digitSum][1] = number;
        }
        int bestResult = -1;
        for (std::vector<int> const &numbers : bestNumbers)
        {
            if (numbers.size() == 2)
                bestResult = std::max(bestResult, numbers[0] + numbers[1]);
        }
        return bestResult;
    }

private:
    [[nodiscard]] int calcDigitSum(int number) const
    {
        int digitSum = 0;
        while (number > 0)
        {
            digitSum += (number % 10);
            number /= 10;
        }
        return digitSum;
    }
};

}

namespace MaxSumPairWithEqualDigitsSumTask
{

TEST(MaxSumPairWithEqualDigitsSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(54, solution.maximumSum({18, 43, 36, 13, 7}));
    ASSERT_EQ(-1, solution.maximumSum({10, 12, 19, 14}));
}

}