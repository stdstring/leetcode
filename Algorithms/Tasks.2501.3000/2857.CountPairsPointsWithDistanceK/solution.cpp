#include <map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countPairs(std::vector<std::vector<int>> const &coordinates, int k) const
    {
        typedef std::pair<int, int> TPoint;
        std::map<TPoint, size_t> knownPoint;
        size_t pairsCount = 0;
        for (std::vector<int> const &point : coordinates)
        {
            const int x1 = point[0];
            const int y1 = point[1];
            for (int x = 0; x <= k; ++x)
            {
                const int y = k - x;
                const int x2 = x1 ^ x;
                const int y2 = y1 ^ y;
                auto iterator = knownPoint.find(TPoint(x2, y2));
                if (iterator != knownPoint.cend())
                    pairsCount += iterator->second;
            }
            ++knownPoint[TPoint(x1, y1)];
        }
        return static_cast<int>(pairsCount);
    }
};

}

namespace CountPairsPointsWithDistanceKTask
{

TEST(CountPairsPointsWithDistanceKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countPairs({{1, 2}, {4, 2}, {1, 3}, {5, 2}}, 5));
    ASSERT_EQ(10, solution.countPairs({{1, 3}, {1, 3}, {1, 3}, {1, 3}, {1, 3}}, 0));
}

}