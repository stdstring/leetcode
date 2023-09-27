#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> corpFlightBookings(std::vector<std::vector<int>> const &bookings, int n) const
    {
        std::vector<int> result(n, 0);
        for (std::vector<int> const &booking : bookings)
        {
            result[booking[0] - 1] += booking[2];
            if (booking[1] < n)
                result[booking[1]] -= booking[2];
        }
        for (size_t index = 1; index < result.size(); ++index)
            result[index] += result[index - 1];
        return result;
    }
};

}

namespace CorporateFlightBookingsTask
{

TEST(CorporateFlightBookingsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({10, 55, 45, 25, 25}), solution.corpFlightBookings({{1, 2, 10}, {2, 3, 20}, {2, 5, 25}}, 5));
    ASSERT_EQ(std::vector<int>({10, 25}), solution.corpFlightBookings({{1, 2, 10}, {2, 2, 15}}, 2));
}

}