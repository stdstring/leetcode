#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDistance(std::vector<int> const &position, int m) const
    {
        std::vector<int> sortedPositions(position);
        std::ranges::sort(sortedPositions);
        if (m == 2)
            return sortedPositions.back() - sortedPositions.front();
        int left = 1;
        int right = sortedPositions.back() - sortedPositions.front();
        while ((right - left) > 1)
        {
            const int middle = (left + right) / 2;
            if (canDistribute(sortedPositions, middle, m))
                left = middle;
            else
                right = middle - 1;
        }
        return canDistribute(sortedPositions, right, m) ? right : left;
    }

private:
    [[nodiscard]] bool canDistribute(std::vector<int> const &positions, int distance, int count) const
    {
        int start = positions[0];
        int distributed = 1;
        for (const int position : positions)
        {
            const int delta = position - start;
            if (delta >= distance)
            {
                start = position;
                ++distributed;
            }
            if (distributed == count)
                return true;
        }
        return false;
    }
};

}

namespace MagneticForceBetweenTwoBallsTask
{

TEST(MagneticForceBetweenTwoBallsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxDistance({1, 2, 3, 4, 7}, 3));
    ASSERT_EQ(999999999, solution.maxDistance({5, 4, 3, 2, 1, 1000000000}, 2));
}

TEST(MagneticForceBetweenTwoBallsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxDistance({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4));
}

}