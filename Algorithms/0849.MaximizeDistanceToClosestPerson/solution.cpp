#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxDistToClosest(std::vector<int> const &seats) const
    {
        size_t maxDistance = 0;
        size_t leftPerson = seats.size();
        for (size_t index = 0; index < seats.size(); ++index)
        {
            if (seats[index] == 1)
            {
                size_t currentDistance = leftPerson == seats.size() ? index : (index - leftPerson) / 2;
                maxDistance = std::max(maxDistance, currentDistance);
                leftPerson = index;
            }
        }
        maxDistance = std::max(maxDistance, seats.size() - 1 - leftPerson);
        return static_cast<int>(maxDistance);
    }
};

}

namespace MaximizeDistanceToClosestPersonTask
{

TEST(MaximizeDistanceToClosestPersonTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.maxDistToClosest({1, 0, 0, 0, 1, 0, 1}));
    ASSERT_EQ(3, solution.maxDistToClosest({1, 0, 0, 0}));
    ASSERT_EQ(1, solution.maxDistToClosest({0, 1}));
}

}