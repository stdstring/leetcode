#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumDeviation(std::vector<int> const &nums) const
    {
        std::priority_queue<int> queue;
        int minNumber = INT_MAX;
        for (const int number : nums)
        {
            int current = (number % 2 == 0) ? number : 2 * number;
            queue.push(current);
            minNumber = std::min(minNumber, current);
        }
        int minDeviation = INT_MAX;
        while ((queue.top() % 2) == 0)
        {
            minDeviation = std::min(minDeviation, queue.top() - minNumber);
            int current = queue.top() / 2;
            queue.pop();
            minNumber = std::min(minNumber, current);
            queue.push(current);
        }
        return std::min(minDeviation, queue.top() - minNumber);
    }
};

}

namespace MinimizeDeviationInArrayTask
{

TEST(MinimizeDeviationInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minimumDeviation({1, 2, 3, 4}));
    ASSERT_EQ(3, solution.minimumDeviation({4, 1, 5, 20, 3}));
    ASSERT_EQ(3, solution.minimumDeviation({2, 10, 8}));
}

TEST(MinimizeDeviationInArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(8360239, solution.minimumDeviation({195643978, 105493962, 103599601, 194267446}));
    ASSERT_EQ(1, solution.minimumDeviation({3, 5}));
    ASSERT_EQ(688266, solution.minimumDeviation({195643978, 194267446}));
    ASSERT_EQ(315, solution.minimumDeviation({399, 908, 648, 357, 693, 502, 331, 649, 596, 698}));
}

}