#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumCandies(std::vector<int> const &candies, long long k) const
    {
        int maxCandies = std::ranges::max(candies);
        int left = 0;
        int right = maxCandies;
        while ((right - left) > 1)
        {
            int middle = (left + right) / 2;
            if (canDistribute(candies, k, middle))
                left = middle;
            else
                right = middle - 1;
        }
        return canDistribute(candies, k, right) ? right : left;
    }

private:
    [[nodiscard]] bool canDistribute(std::vector<int> const &candies, long long k, int candyPerChild) const
    {
        if (candyPerChild == 0)
            return true;
        for (const int currentCandies : candies)
        {
            const long long childrenCount = currentCandies / candyPerChild;
            if (childrenCount >= k)
                return true;
            k -= childrenCount;
        }
        return false;
    }
};

}

namespace MaxCandiesAllocatedKChildrenTask
{

TEST(MaxCandiesAllocatedKChildrenTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maximumCandies({5, 8, 6}, 3));
    ASSERT_EQ(0, solution.maximumCandies({2, 5}, 11));
}

TEST(MaxCandiesAllocatedKChildrenTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.maximumCandies({4, 7, 5}, 17));
}

}