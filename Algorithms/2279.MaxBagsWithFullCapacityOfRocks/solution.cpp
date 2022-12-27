#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumBags(std::vector<int> const &capacity, std::vector<int> const &rocks, int additionalRocks) const
    {
        std::vector<int> rest(capacity.size(), 0);
        for (size_t index = 0; index < rest.size(); ++index)
            rest[index] = capacity[index] - rocks[index];
        std::sort(rest.begin(), rest.end());
        size_t fullCapacityBags = 0;
        for (const int restValue : rest)
        {
            if (additionalRocks < restValue)
                break;
            ++fullCapacityBags;
            additionalRocks -= restValue;
        }
        return static_cast<int>(fullCapacityBags);
    }
};

}

namespace MaxBagsWithFullCapacityOfRocksTask
{

TEST(MaxBagsWithFullCapacityOfRocksTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumBags({2, 3, 4, 5}, {1, 2, 4, 4}, 2));
    ASSERT_EQ(3, solution.maximumBags({10, 2, 2}, {2, 2, 0}, 100));
}

}