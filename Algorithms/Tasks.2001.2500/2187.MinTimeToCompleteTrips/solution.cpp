#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumTime(std::vector<int> const &time, int totalTrips) const
    {
        if (time.size() == 1)
            return 1LL * time.front() * totalTrips;
        // find range
        long long left = *std::min_element(time.cbegin(), time.cend());
        if (totalTrips <= calcTotalTrips(time, left))
            return left;
        long long right = 10LL * left;
        int rightTotalTrips = calcTotalTrips(time, right);
        while (rightTotalTrips < totalTrips)
        {
            left = right;
            right *= 10LL;
            rightTotalTrips = calcTotalTrips(time, right);
        }
        if (totalTrips == rightTotalTrips)
            return right;
        // find in range [left, right]
        while (left < right)
        {
            const long long middle = (left + right) / 2LL;
            const int middleTotalTrips = calcTotalTrips(time, middle);
            if (middleTotalTrips < totalTrips)
                left = middle + 1;
            else
                right = middle;
        }
        return left;
    }

private:
    [[nodiscard]] int calcTotalTrips(std::vector<int> const &times, long long totalTime) const
    {
        int totalTrips = 0;
        for (const int time : times)
            totalTrips += static_cast<int>(totalTime / time);
        return totalTrips;
    }
};

}

namespace MinTimeToCompleteTripsTask
{

TEST(MinTimeToCompleteTripsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumTime({1, 2, 3}, 5));
    ASSERT_EQ(2, solution.minimumTime({2}, 1));
}

TEST(MinTimeToCompleteTripsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(25, solution.minimumTime({5, 10, 10}, 9));
}

}