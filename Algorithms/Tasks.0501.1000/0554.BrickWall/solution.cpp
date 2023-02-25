#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int leastBricks(std::vector<std::vector<int>> const &wall) const
    {
        std::unordered_map<int, size_t> edges;
        size_t maxEdgesOnLine = 0;
        for (std::vector<int> const &line : wall)
        {
            int width = 0;
            for (size_t index = 0; index < line.size() - 1; ++index)
            {
                width += line[index];
                edges[width] = edges[width] + 1;
                maxEdgesOnLine = std::max(maxEdgesOnLine, edges[width]);
            }
        }
        return static_cast<int>(wall.size() - maxEdgesOnLine);
    }
};

}

namespace BrickWallTask
{

TEST(BrickWallTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.leastBricks({{1, 2, 2, 1}, {3, 1, 2}, {1, 3, 2}, {2, 4}, {3, 1, 2}, {1, 3, 1, 1}}));
}

}