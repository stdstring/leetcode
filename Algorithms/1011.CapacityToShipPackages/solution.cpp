#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int shipWithinDays(std::vector<int> const &weights, int days) const
    {
        int totalCapacity = 0;
        int maxWeight = 0;
        for (const int weight : weights)
        {
            totalCapacity += weight;
            maxWeight = std::max(maxWeight, weight);
        }
        int left = maxWeight;
        int right = totalCapacity;
        while (right > left)
        {
            const int middle = (left + right) / 2;
            if (isFeasible(weights, middle, days))
                right = middle;
            else
                left = middle + 1;
        }
        return left;
    }

private:
    [[nodiscard]] bool isFeasible(std::vector<int> const &weights, int maxCapacity, int days) const
    {
        int currentDays = 1;
        int currentCapacity = 0;
        for (const int weight : weights)
        {
            currentCapacity += weight;
            if (currentCapacity > maxCapacity)
            {
                ++currentDays;
                currentCapacity = weight;
            }
        }
        return currentDays <= days;
    }
};

}

namespace CapacityToShipPackagesTask
{

TEST(CapacityToShipPackagesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.shipWithinDays({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5));
    ASSERT_EQ(6, solution.shipWithinDays({3, 2, 2, 4, 1, 4}, 3));
    ASSERT_EQ(3, solution.shipWithinDays({1, 2, 3, 1, 1}, 4));
}

TEST(CapacityToShipPackagesTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.shipWithinDays({ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }, 5));
}

}