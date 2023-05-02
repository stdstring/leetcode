#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int carFleet(int target, std::vector<int> const &position, std::vector<int> const &speed) const
    {
        std::vector<size_t> indices(position.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&position](size_t l, size_t r) { return position[l] > position[r]; });
        size_t fleetCount = 1;
        double lastArriveTime = 1.0 * (target - position[indices.front()]) / speed[indices.front()];
        for (size_t index = 1; index < indices.size(); ++index)
        {
            const double currentArriveTime = 1.0 * (target - position[indices[index]]) / speed[indices[index]];
            if (currentArriveTime > lastArriveTime)
            {
                lastArriveTime = currentArriveTime;
                ++fleetCount;
            }
        }
        return static_cast<int>(fleetCount);
    }
};

}

namespace CarFleetTask
{

TEST(CarFleetTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.carFleet(12, {10, 8, 0, 5, 3}, {2, 4, 1, 1, 3}));
    ASSERT_EQ(1, solution.carFleet(10, {3}, {3}));
    ASSERT_EQ(1, solution.carFleet(100, {0, 2, 4}, {4, 2, 1}));
}

}