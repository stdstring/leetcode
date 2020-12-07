#include <algorithm>
#include <queue>
#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int nthUglyNumber(int n) const
    {
        std::queue<int> factor2({1});
        std::queue<int> factor3({1});
        std::queue<int> factor5({1});
        int uglyNumber = 1;
        for (int number = 2; number <= n; ++number)
        {
            int candidate2 = 2 * factor2.front();
            int candidate3 = 3 * factor3.front();
            int candidate5 = 5 * factor5.front();
            uglyNumber = std::min(candidate2, std::min(candidate3, candidate5));
            if (candidate2 == uglyNumber)
                factor2.pop();
            if (candidate3 == uglyNumber)
                factor3.pop();
            if (candidate5 == uglyNumber)
                factor5.pop();
            factor2.push(uglyNumber);
            factor3.push(uglyNumber);
            factor5.push(uglyNumber);
        }
        return uglyNumber;
    }
};

}

namespace UglyNumberIITask
{

TEST(UglyNumberIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(12, solution.nthUglyNumber(10));
}

}