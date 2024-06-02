#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> gardenNoAdj(int n, std::vector<std::vector<int>> const &paths) const
    {
        std::vector<std::vector<int>> nodes(n);
        for (std::vector<int> const &path : paths)
        {
            const int sideA = path[0] - 1;
            const int sideB = path[1] - 1;
            nodes[sideA].emplace_back(sideB);
            nodes[sideB].emplace_back(sideA);
        }
        std::vector<int> colors(n, 0);
        for (int node = 0; node < n; ++node)
        {
            if (colors[node] != 0)
                continue;
            std::queue<int> queue;
            queue.emplace(node);
            while (!queue.empty())
            {
                const int current = queue.front();
                queue.pop();
                if (colors[current] != 0)
                    continue;
                colors[current] = chooseColor(nodes[current], colors);
                for (const int neighbor : nodes[current])
                {
                    if (colors[neighbor] == 0)
                        queue.emplace(neighbor);
                }
            }
        }
        return colors;
    }

private:
    [[nodiscard]] int chooseColor(std::vector<int> const &node, std::vector<int> const &colors) const
    {
        constexpr int color1 = 0b0001;
        constexpr int color2 = 0b0010;
        constexpr int color3 = 0b0100;
        constexpr int color4 = 0b1000;
        int usedColors = 0;
        for (const int neighbor : node)
        {
            if (colors[neighbor] != 0)
                usedColors |= (1 << (colors[neighbor] - 1));
        }
        if ((usedColors & color1) == 0)
            return 1;
        if ((usedColors & color2) == 0)
            return 2;
        if ((usedColors & color3) == 0)
            return 3;
        if ((usedColors & color4) == 0)
            return 4;
        return -1;
    }
};

}

namespace FlowerPlantingWithNoAdjacentTask
{

TEST(FlowerPlantingWithNoAdjacentTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3}), solution.gardenNoAdj(3, {{1, 2}, {2, 3}, {3, 1}}));
    ASSERT_EQ(std::vector<int>({1, 2, 1, 2}), solution.gardenNoAdj(4, {{1, 2}, {3, 4}}));
    ASSERT_EQ(std::vector<int>({1, 2, 4, 3}), solution.gardenNoAdj(4, {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 3}, {2, 4}}));
}

}