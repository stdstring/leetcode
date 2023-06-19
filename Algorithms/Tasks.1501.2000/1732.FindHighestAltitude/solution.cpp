#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestAltitude(std::vector<int> const &gain) const
    {
        int bestAltitude = 0;
        int currentAltitude = 0;
        for (const int delta : gain)
        {
            currentAltitude += delta;
            bestAltitude = std::max(bestAltitude, currentAltitude);
        }
        return bestAltitude;
    }
};

}

namespace FindHighestAltitudeTask
{

TEST(FindHighestAltitudeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.largestAltitude({-5, 1, 5, 0, -7}));
    ASSERT_EQ(0, solution.largestAltitude({-4, -3, -2, -1, 4, 3, 2}));
}

}