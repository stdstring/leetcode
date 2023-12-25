#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long distributeCandies(int n, int limit) const
    {
        long long result = 0;
        for (int first = n / 3 + (n % 3 > 0 ? 1 : 0); (first <= n) && (first <= limit); ++first)
        {
            if ((3 * first) == n)
            {
                ++result;
                continue;
            }
            int rest = n - first;
            const int secondStart = rest / 2 + (rest % 2 > 0 ? 1 : 0);
            if (secondStart > first)
                continue;
            if (secondStart == first)
            {
                result += 3;
                continue;
            }
            result += 6LL * (std::min(first, rest) - secondStart + 1);
            if (rest % 2 == 0)
                result -= 3;
            if ((secondStart < first) && (first <= rest))
                result -= 3;
        }
        return result;
    }
};

}

namespace DistributeCandiesAmongChildren2Task
{

TEST(DistributeCandiesAmongChildren2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.distributeCandies(5, 2));
    ASSERT_EQ(10, solution.distributeCandies(3, 3));
}

TEST(DistributeCandiesAmongChildren2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.distributeCandies(4, 2));
}

}