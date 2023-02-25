#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

enum class Color { None = 0, Red = 1, Blue = 2 };

class Solution
{
public:
    bool isBipartite(std::vector<std::vector<int>> const &graph) const
    {
        std::vector<Color> colors(graph.size(), Color::None);
        std::vector<bool> processedNodes(graph.size(), false);
        for (size_t index = 0; index < graph.size(); ++index)
        {
            if (processedNodes[index])
                continue;
            std::queue<size_t> queue;
            colors[index] = Color::Red;
            queue.push(index);
            while (!queue.empty())
            {
                if (!processedNodes[queue.front()])
                {
                    const Color currentColor = colors[queue.front()];
                    const Color otherColor = currentColor == Color::Red ? Color::Blue : Color::Red;
                    for (int neighbor : graph[queue.front()])
                    {
                        if (colors[neighbor] == currentColor)
                            return false;
                        if (processedNodes[neighbor])
                            continue;
                        colors[neighbor] = otherColor;
                        queue.push(neighbor);
                    }
                    processedNodes[queue.front()] = true;
                }
                queue.pop();
            }
        }
        return true;
    }
};

}

namespace IsGraphBipartiteTask
{

TEST(IsGraphBipartiteTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isBipartite({{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}}));
    ASSERT_EQ(true, solution.isBipartite({{1, 3}, {0, 2}, {1, 3}, {0, 2}}));
}

}