#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestSquareStreak(std::vector<int> const &nums) const
    {
        std::map<long long, bool> numberMap;
        for (int number : nums)
            numberMap.emplace(number, false);
        const long long maxNumber = numberMap.crbegin()->first;
        size_t bestSubsequence = 0;
        for (auto current = numberMap.cbegin(); current != numberMap.cend(); ++current)
        {
            if (current->second)
                continue;
            size_t currentSubsequence = 0;
            long long currentNumber = current->first;
            while (currentNumber <= maxNumber)
            {
                auto iterator = numberMap.find(currentNumber);
                if (iterator == numberMap.cend())
                    break;
                iterator->second = true;
                ++currentSubsequence;
                currentNumber *= currentNumber;
            }
            if (currentSubsequence > 1)
                bestSubsequence = std::max(bestSubsequence, currentSubsequence);
        }
        return bestSubsequence == 0 ? -1 : static_cast<int>(bestSubsequence);
    }
};

}

namespace LongestSquareStreakInArrayTask
{

TEST(LongestSquareStreakInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.longestSquareStreak({4, 3, 6, 16, 8, 2}));
    ASSERT_EQ(-1, solution.longestSquareStreak({2, 3, 5, 6, 7}));
}

TEST(LongestSquareStreakInArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.longestSquareStreak({4, 16, 256, 65536}));
}

}