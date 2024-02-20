#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> countOfPairs(int n, int x, int y) const
    {
        std::vector<int> distancePairs(n, 0);
        for (int start = 1; start <= n; ++start)
            calcDistanceFromHouse(n, x - 1, y - 1, start - 1, distancePairs);
        return distancePairs;
    }

private:
    void calcDistanceFromHouse(int n, int x, int y, int start, std::vector<int> &distancePairs) const
    {
        std::vector<bool> visited(n, false);
        visited[start] = true;
        // house, distance
        std::queue<std::pair<int, int>> housesQueue;
        housesQueue.emplace(start, 0);
        while (!housesQueue.empty())
        {
            auto [current, distance] = housesQueue.front();
            housesQueue.pop();
            if ((current < (n - 1)) && !visited[current + 1])
            {
                housesQueue.emplace(current + 1, distance + 1);
                visited[current + 1] = true;
                ++distancePairs[distance];
            }
            if ((current > 0) && !visited[current - 1])
            {
                housesQueue.emplace(current - 1, distance + 1);
                visited[current - 1] = true;
                ++distancePairs[distance];
            }
            if ((current == x) && !visited[y])
            {
                housesQueue.emplace(y, distance + 1);
                visited[y] = true;
                ++distancePairs[distance];
            }
            if ((current == y) && !visited[x])
            {
                housesQueue.emplace(x, distance + 1);
                visited[x] = true;
                ++distancePairs[distance];
            }
        }
    }
};

}

namespace CountNumberHousesAtCertainDistance1Task
{

TEST(CountNumberHousesAtCertainDistance1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({6, 0, 0}), solution.countOfPairs(3, 1, 3));
    ASSERT_EQ(std::vector<int>({10, 8, 2, 0, 0}), solution.countOfPairs(5, 2, 4));
    ASSERT_EQ(std::vector<int>({6, 4, 2, 0}), solution.countOfPairs(4, 1, 1));
}

}