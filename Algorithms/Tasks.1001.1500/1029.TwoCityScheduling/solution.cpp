#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int twoCitySchedCost(std::vector<std::vector<int>> const &costs) const
    {
        auto comp = [](std::vector<int> const &left, std::vector<int> const &right){
            const int leftMin = std::min(left[0], left[1]);
            const int leftDelta = std::abs(left[0] - left[1]);
            const int rightMin = std::min(right[0], right[1]);
            const int rightDelta = std::abs(right[0] - right[1]);
            return (leftDelta > rightDelta) || ((leftDelta == rightDelta) && (leftMin < rightMin));
        };
        std::vector<std::vector<int>> sortedCosts(costs);
        std::sort(sortedCosts.begin(), sortedCosts.end(), comp);
        size_t n = sortedCosts.size() / 2;
        size_t firstCount = 0;
        size_t secondCount = 0;
        int totalCost = 0;
        for (std::vector<int> const &cost : sortedCosts)
        {
            int firstCost = cost[0];
            int secondCost = cost[1];
            if (firstCost < secondCost)
            {
                totalCost += (firstCount < n ? firstCost : secondCost);
                ++(firstCount < n ? firstCount : secondCount);
            }
            else
            {
                totalCost += (secondCount < n ? secondCost : firstCost);
                ++(secondCount < n ? secondCount : firstCount);
            }
        }
        return totalCost;
    }
};

}

namespace TwoCitySchedulingTask
{

TEST(TwoCitySchedulingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(110, solution.twoCitySchedCost({{10, 20}, {30, 200}, {400, 50}, {30, 20}}));
    ASSERT_EQ(1859, solution.twoCitySchedCost({{259, 770}, {448, 54}, {926, 667}, {184, 139}, {840, 118}, {577, 469}}));
    ASSERT_EQ(3086, solution.twoCitySchedCost({{515, 563}, {451, 713}, {537, 709}, {343, 819}, {855, 779}, {457, 60}, {650, 359}, {631, 42}}));
}

}
