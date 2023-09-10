#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canArrange(std::vector<int> const &arr, int k) const
    {
        std::unordered_map<int, size_t> reminderMap;
        for (const int number : arr)
        {
            int reminder = number % k;
            if (reminder < 0)
                reminder += k;
            ++reminderMap[reminder];
        }
        for (auto const &[reminder, count] : reminderMap)
        {
            if (reminder == 0)
            {
                if ((count % 2) != 0)
                    return false;
            }
            else
            {
                int pairReminder = k - reminder;
                if (count != reminderMap[pairReminder])
                    return false;
            }
        }
        return true;
    }
};

}

namespace CheckIfArrayPairsDivisibleByKTask
{

TEST(CheckIfArrayPairsDivisibleByKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canArrange({1, 2, 3, 4, 5, 10, 6, 7, 8, 9}, 5));
    ASSERT_EQ(true, solution.canArrange({1, 2, 3, 4, 5, 6}, 7));
    ASSERT_EQ(false, solution.canArrange({1, 2, 3, 4, 5, 6}, 10));
}

TEST(CheckIfArrayPairsDivisibleByKTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canArrange({-1, 1, -2, 2, -3, 3, -4, 4}, 3));
}

}