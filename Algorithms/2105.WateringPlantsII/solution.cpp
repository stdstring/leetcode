#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumRefill(std::vector<int> const &plants, int capacityA, int capacityB) const
    {
        size_t refillCount = 0;
        size_t left = 0;
        size_t right = plants.size() - 1;
        int currentCapacityA = capacityA;
        int currentCapacityB = capacityB;
        while (left < right)
        {
            if (currentCapacityA < plants[left])
            {
                ++refillCount;
                currentCapacityA = capacityA;
            }
            currentCapacityA -= plants[left++];
            if (currentCapacityB < plants[right])
            {
                ++refillCount;
                currentCapacityB = capacityB;
            }
            currentCapacityB -= plants[right--];
        }
        if ((left == right) && (std::max(currentCapacityA, currentCapacityB) < plants[left]))
            ++refillCount;
        return static_cast<int>(refillCount);
    }
};

}

namespace WateringPlantsIITask
{

TEST(WateringPlantsIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minimumRefill({2, 2, 3, 3}, 5, 5));
    ASSERT_EQ(2, solution.minimumRefill({2, 2, 3, 3}, 3, 4));
    ASSERT_EQ(0, solution.minimumRefill({5}, 10, 8));
}

}