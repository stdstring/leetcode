#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Graph
{
public:
    Graph(int n, std::vector<std::vector<int>> const &edges) : _nodes(n)
    {
        for (std::vector<int> const &edge : edges)
        {
            const int fromNode = edge[0];
            const int toNode = edge[1];
            const int cost = edge[2];
            _nodes[fromNode].emplace_back(toNode, cost);
        }
    }

    void addEdge(std::vector<int> const &edge)
    {
        const int fromNode = edge[0];
        const int toNode = edge[1];
        const int cost = edge[2];
        _nodes[fromNode].emplace_back(toNode, cost);
    }

    int shortestPath(int node1, int node2) const
    {
        const size_t nodeCount = _nodes.size();
        std::vector<int> costs(nodeCount, INT_MAX);
        std::vector<bool> visited(nodeCount, false);
        auto cmp = [](Target const &left, Target const &right) { return left.Cost > right.Cost; };
        std::priority_queue<Target, std::vector<Target>, decltype(cmp)> queue(cmp);
        costs[node1] = 0;
        queue.emplace(node1, 0);
        while (!queue.empty())
        {
            const Target current(queue.top());
            queue.pop();
            if (visited[current.Node])
                continue;
            visited[current.Node] = true;
            for (Target const &neighbor : _nodes[current.Node])
            {
                if (visited[neighbor.Node])
                    continue;
                const int cost = current.Cost + neighbor.Cost;
                if (cost < costs[neighbor.Node])
                {
                    queue.emplace(neighbor.Node, cost);
                    costs[neighbor.Node] = cost;
                }
            }
        }
        return costs[node2] < INT_MAX ? costs[node2] : -1;
    }

private:
    struct Target
    {
        Target(int node, int cost) : Node(node), Cost(cost)
        {
        }

        int Node;
        int Cost;
    };

    std::vector<std::vector<Target>> _nodes;
};

}

namespace DesignGraphWithShortestPathCalculatorTask
{

TEST(DesignGraphWithShortestPathCalculatorTaskTests, Examples)
{
    Graph graph(4, {{0, 2, 5}, {0, 1, 2}, {1, 2, 1}, {3, 0, 3}});
    ASSERT_EQ(6, graph.shortestPath(3, 2));
    ASSERT_EQ(-1, graph.shortestPath(0, 3));
    ASSERT_NO_THROW(graph.addEdge({1, 3, 4}));
    ASSERT_EQ(6, graph.shortestPath(0, 3));
}

}