#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findRedundantConnection(std::vector<std::vector<int>> const &edges) const
    {
        const size_t nodesCount = edges.size();
        std::vector<NodeData> nodes(nodesCount, NodeData());
        for (std::vector<int> const &edge : edges)
        {
            const int node1 = edge[0] - 1;
            const int parent1 = getParent(nodes, node1);
            const int node2 = edge[1] - 1;
            const int parent2 = getParent(nodes, node2);
            if (parent1 == parent2)
                return edge;
            if (nodes[parent1].Size >= nodes[parent2].Size)
            {
                nodes[parent2].Parent = parent1;
                nodes[parent1].Size += nodes[parent2].Size;
            }
            else
            {
                nodes[parent1].Parent = parent2;
                nodes[parent2].Size += nodes[parent1].Size;
            }
        }
        return {-1, -1};
    }

private:
    struct NodeData
    {
        NodeData() = default;

        int Parent = -1;
        size_t Size = 1;
    };

    [[nodiscard]] int getParent(std::vector<NodeData> const &data, int current) const
    {
        while (data[current].Parent != -1)
            current = data[current].Parent;
        return current;
    }
};

}

namespace RedundantConnectionTask
{

TEST(RedundantConnectionTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 3}), solution.findRedundantConnection({{1, 2}, {1, 3}, {2, 3}}));
    ASSERT_EQ(std::vector<int>({1, 4}), solution.findRedundantConnection({{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}}));
}

}