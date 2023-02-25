#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int integerBreak(int n) const
    {
        if (n == 2)
            return 1;
        std::vector<size_t> maxProduct(n + 1, 0);
        // 1 + 1 = 2, maxProduct[2] = 1 * 1 = 1
        maxProduct[2] = 1;
        // 1 + 2 = 3, maxProduct[3] = 1 * 2 = 2
        maxProduct[3] = 2;
        // Anyone can show the following (for k => 1):
        // maxProduct[3 * k + 1] = 2 * max(3 * k - 1, maxProduct[3 * k - 1])
        // maxProduct[3 * k + 2] = 2 * max(3 * k, maxProduct[3 * k])
        // maxProduct[3 * k + 3] = 3 * max(3 * k, maxProduct[3 * k])
        for (size_t number = 4; number <= static_cast<size_t>(n); ++number)
        {
            const size_t factor = number % 3 != 0 ? 2 : 3;
            maxProduct[number] = factor * std::max(maxProduct[number - factor], (number - factor));
        }
        return static_cast<int>(maxProduct[n]);
    }
};

}

namespace IntegerBreakTask
{

TEST(IntegerBreakTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.integerBreak(2));
    ASSERT_EQ(36, solution.integerBreak(10));
}

}