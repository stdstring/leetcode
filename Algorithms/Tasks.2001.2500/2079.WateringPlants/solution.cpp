#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int wateringPlants(std::vector<int> const &plants, int capacity) const
    {
        size_t steps = 0;
        int currentWaterRest = capacity;
        for (size_t index = 0; index < plants.size(); ++index)
        {
            if (currentWaterRest < plants[index])
            {
                steps += 2 * index;
                currentWaterRest = capacity;
            }
            ++steps;
            currentWaterRest -= plants[index];
        }
        return static_cast<int>(steps);
    }
};

}

namespace WateringPlantsTask
{

TEST(WateringPlantsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(14, solution.wateringPlants({2, 2, 3, 3}, 5));
    ASSERT_EQ(30, solution.wateringPlants({1, 1, 1, 4, 2, 3}, 4));
    ASSERT_EQ(49, solution.wateringPlants({7, 7, 7, 7, 7, 7, 7}, 8));
}

}