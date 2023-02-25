#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numSquares(int n) const
    {
        std::vector<int> squares(getPerfectSquares(n));
        std::vector<int> result(n, INT_MAX);
        for (int square : squares)
            result[square - 1] = 1;
        for (int number = 1; number < n; ++number)
        {
            for (int square : squares)
            {
                if (number + square > n)
                    break;
                result[number + square - 1] = std::min(result[number + square - 1], result[number - 1] + 1);
            }
        }
        return result[n - 1];
    }

private:
    std::vector<int> getPerfectSquares(int n) const
    {
        std::vector<int> squares;
        for (int root = 1; root * root <= n; ++root)
            squares.push_back(root * root);
        return squares;
    }
};

}

namespace PerfectSquaresTask
{

TEST(PerfectSquaresTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numSquares(12));
    ASSERT_EQ(2, solution.numSquares(13));
}

}