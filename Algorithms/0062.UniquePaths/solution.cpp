#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int uniquePaths(int m, int n) const
    {
        const int horizontalSegments = m - 1;
        const int verticalSegments = n - 1;
        const int pathSegments = horizontalSegments + verticalSegments;
        // calc binomial coefficient
        long long result = 1;
        for (int number = std::max(horizontalSegments, pathSegments - horizontalSegments) + 1; number <= pathSegments; ++number)
            result *= number;
        for (int number = 2; number <= std::min(horizontalSegments, pathSegments - horizontalSegments); ++number)
            result /= number;
        return static_cast<int>(result);
    }
};

}

namespace UniquePathsTask
{

TEST(UniquePathsTask, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.uniquePaths(3, 2));
    ASSERT_EQ(28, solution.uniquePaths(7, 3));
}

}