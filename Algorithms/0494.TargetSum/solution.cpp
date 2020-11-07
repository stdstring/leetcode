#include <array>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findTargetSumWays(std::vector<int> const &nums, int S) const
    {
        constexpr int maxSum = 1000;
        constexpr int size = 2 * maxSum + 1;
        std::array<int, size> currentData{};
        currentData.fill(0);
        currentData[nums[0] + maxSum] += 1;
        currentData[-nums[0] + maxSum] += 1;
        std::array<int, size> nextData{};
        for (size_t index = 1; index < nums.size(); ++index)
        {
            for (int currentIndex = 0; currentIndex < size; ++currentIndex)
            {
                if (currentData[currentIndex] != 0)
                {
                    const int currentSum = currentIndex - maxSum;
                    nextData[maxSum + currentSum + nums[index]] += currentData[currentIndex];
                    nextData[maxSum + currentSum - nums[index]] += currentData[currentIndex];
                    currentData[currentIndex] = 0;
                }
            }
            nextData.swap(currentData);
        }
        return S > maxSum ? 0 : currentData[maxSum + S];
    }
};

}

namespace TargetSumTask
{

TEST(TargetSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.findTargetSumWays({1, 1, 1, 1, 1}, 3));
}

TEST(TargetSumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findTargetSumWays({1, 0}, 1));
    ASSERT_EQ(0, solution.findTargetSumWays({1, 2, 7, 9, 981}, 1000000000));
    ASSERT_EQ(0, solution.findTargetSumWays({2, 107, 109, 113, 127, 131, 137, 3, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 47, 53}, 2147483647));
}

}