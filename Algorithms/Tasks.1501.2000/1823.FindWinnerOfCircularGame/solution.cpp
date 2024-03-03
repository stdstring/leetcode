#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findTheWinner(int n, int k) const
    {
        // e.g. n = 7, k = 4
        // we have the following indices (in cyclic list): 0, 1, 2, 3, 4, 5, 6
        // after removing k=4 element (with indices 3): 0, 1, 2, 4, 5, 6
        // after rearranging: 4, 5, 6, 0, 1, 2
        // after renaming (4 -> 0, 5 -> 1, 6 -> 2, 0 -> 3, 1 -> 4, 2 -> 5): 0, 1, 2, 3, 4, 5
        // so formula for conversion of indices: (findTheWinner(n-1, k) + k) % n
        return 1 + findTheWinnerImpl(n, k);
    }

private:
    [[nodiscard]] int findTheWinnerImpl(int n, int k) const
    {
        if (n == 1)
            return 0;
        return (findTheWinnerImpl(n - 1, k) + k) % n;
    }
};

}

namespace FindWinnerOfCircularGameTask
{

TEST(FindWinnerOfCircularGameTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.findTheWinner(5, 2));
    ASSERT_EQ(1, solution.findTheWinner(6, 5));
}

}