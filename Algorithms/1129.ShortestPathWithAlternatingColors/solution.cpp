#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> shortestAlternatingPaths(int n, std::vector<std::vector<int>> const &redEdges, std::vector<std::vector<int>> const &blueEdges) const
    {
        std::vector<Node> nodes(n, Node());
        for (std::vector<int> const &edge : redEdges)
            nodes[edge[0]].RedLinks.push_back(edge[1]);
        for (std::vector<int> const &edge : blueEdges)
            nodes[edge[0]].BlueLinks.push_back(edge[1]);
        constexpr int blackColor = 0b0;
        constexpr int redColor = 0b01;
        constexpr int blueColor = 0b10;
        constexpr int bothColors = redColor | blueColor;
        std::vector<int> nodeColors(n, 0);
        nodeColors[0] = bothColors;
        std::vector<int> result(n, -1);
        result[0] = 0;
        std::queue<Step> queue;
        queue.emplace(0, 0, blackColor);
        while (!queue.empty())
        {
            auto [node, size, color] = queue.front();
            queue.pop();
            switch (color)
            {
            case blackColor:
                for (const int neighbor : nodes[node].RedLinks)
                    processTransition(neighbor, redColor, size + 1, nodeColors, queue, result);
                for (const int neighbor : nodes[node].BlueLinks)
                    processTransition(neighbor, blueColor, size + 1, nodeColors, queue, result);
                break;
            case redColor:
                for (const int neighbor : nodes[node].BlueLinks)
                    processTransition(neighbor, blueColor, size + 1, nodeColors, queue, result);
                break;
            case blueColor:
                for (const int neighbor : nodes[node].RedLinks)
                    processTransition(neighbor, redColor, size + 1, nodeColors, queue, result);
                break;
            default:
                throw std::logic_error("Unknown color");
            }
        }
        return result;
    }

private:
    struct Node
    {
        Node() = default;

        std::vector<int> RedLinks;
        std::vector<int> BlueLinks;
    };

    struct Step
    {
        Step(int node, int size, int color) : Node(node), Size(size), Color(color)
        {
        }

        int Node;
        int Size;
        int Color;
    };

    void processTransition(int node, int color, int size, std::vector<int> &nodeColors, std::queue<Step> &queue, std::vector<int> &result) const
    {
        if (result[node] == -1)
            result[node] = size;
        if ((nodeColors[node] & color) == 0)
        {
            nodeColors[node] |= color;
            queue.emplace(node, size, color);
        }
    }
};

}

namespace ShortestPathWithAlternatingColorsTask
{

TEST(ShortestPathWithAlternatingColorsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, -1}), solution.shortestAlternatingPaths(3, {{0, 1}, {1, 2}}, {}));
    ASSERT_EQ(std::vector<int>({0, 1, -1}), solution.shortestAlternatingPaths(3, {{0, 1}}, {{2, 1}}));
}

}