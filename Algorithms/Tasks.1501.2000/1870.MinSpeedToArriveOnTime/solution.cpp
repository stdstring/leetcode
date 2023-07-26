#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSpeedOnTime(std::vector<int> const &dist, double hour) const
    {
        const size_t maxPossibleTrains = static_cast<size_t>(std::ceil(hour));
        if (maxPossibleTrains < dist.size())
            return -1;
        // minSpeed = 1, MaxSpeed = 100000 / 0.01 = 10000000
        int leftSpeed = 1;
        int rightSpeed = 10000000;
        while (leftSpeed < rightSpeed)
        {
            const int middle = (leftSpeed + rightSpeed) / 2;
            if (isEnoughTime(dist, middle, hour))
                rightSpeed = middle;
            else
                leftSpeed = middle + 1;
        }
        return leftSpeed;
    }

private:
    [[nodiscard]] bool isEnoughTime(std::vector<int> const &distances, int speed, double availableTime) const
    {
        double currentTime = 0;
        for (const int distance : distances)
        {
            currentTime = std::ceil(currentTime);
            currentTime += static_cast<double>(distance) / static_cast<double>(speed);
            if (currentTime > availableTime)
                return false;
        }
        return true;
    }
};

}

namespace MinSpeedToArriveOnTimeTask
{

TEST(MinSpeedToArriveOnTimeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minSpeedOnTime({1, 3, 2}, 6.0));
    ASSERT_EQ(3, solution.minSpeedOnTime({1, 3, 2}, 2.7));
    ASSERT_EQ(-1, solution.minSpeedOnTime({1, 3, 2}, 1.9));
}

TEST(MinSpeedToArriveOnTimeTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(10000000, solution.minSpeedOnTime({1, 1, 100000}, 2.01));
}

}