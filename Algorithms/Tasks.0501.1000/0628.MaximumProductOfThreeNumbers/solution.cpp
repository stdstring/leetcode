#include <algorithm>
#include <climits>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maximumProduct(std::vector<int> const &nums) const
    {
        int best1 = INT_MIN;
        int best2 = INT_MIN;
        int best3 = INT_MIN;
        int worst1 = INT_MAX;
        int worst2 = INT_MAX;
        for (int number : nums)
            processNumber(number, best1, best2, best3, worst1, worst2);
        return std::max(best1 * best2 * best3, best1 * worst1 * worst2);
    }

private:
    void processNumber(int number, int &best1, int &best2, int &best3, int &worst1, int &worst2) const
    {
        if (number >= best1)
        {
            best3 = best2;
            best2 = best1;
            best1 = number;
        }
        else if (number >= best2)
        {
            best3 = best2;
            best2 = number;
        }
        else if (number > best3)
            best3 = number;
        if (number <= worst1)
        {
            worst2 = worst1;
            worst1 = number;
        }
        else if (number < worst2)
            worst2 = number;
    }
};

}

namespace MaximumProductOfThreeNumbersTask
{

TEST(MaximumProductOfThreeNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.maximumProduct({1, 2, 3}));
    ASSERT_EQ(24, solution.maximumProduct({1, 2, 3, 4}));
    ASSERT_EQ(-6, solution.maximumProduct({-1, -2, -3}));
}

TEST(MaximumProductOfThreeNumbersTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(39200, solution.maximumProduct({-100, -98, -1, 2, 3, 4}));
}

}