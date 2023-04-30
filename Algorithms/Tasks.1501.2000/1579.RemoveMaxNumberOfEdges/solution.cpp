#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxNumEdgesToRemove(int n, std::vector<std::vector<int>> const &edges) const
    {
        constexpr int aliceEdgeType = 1;
        constexpr int bobEdgeType = 2;
        constexpr int commonEdgeType = 3;
        const size_t nodesCount = n;
        std::vector<NodeData> commonData;
        commonData.reserve(nodesCount);
        for (size_t node = 0; node < nodesCount; ++node)
            commonData.emplace_back(node);
        // process type 3: can be traversed by both Alice and Bob
        size_t removedEdges = processEdges(commonData, edges, commonEdgeType);
        // process type 1: can be traversed by Alice only
        std::vector<NodeData> aliceData(commonData);
        removedEdges += processEdges(aliceData, edges, aliceEdgeType);
        if (!canTraverse(aliceData))
            return -1;
        // process type 2: can be traversed by Bob only
        std::vector<NodeData> bobData(commonData);
        removedEdges += processEdges(bobData, edges, bobEdgeType);
        if (!canTraverse(bobData))
            return -1;
        return static_cast<int>(removedEdges);
    }

private:
    struct NodeData
    {
        NodeData(size_t node) : Root(node), Size(1)
        {
        }
        size_t Root;
        size_t Size;
    };

    [[nodiscard]] size_t getRoot(std::vector<NodeData> const &data, size_t current) const
    {
        while (data[current].Root != current)
            current = data[current].Root;
        return current;
    }

    void merge(std::vector<NodeData> &data, size_t root1, size_t root2) const
    {
        if (data[root1].Size >= data[root2].Size)
        {
            data[root2].Root = root1;
            data[root1].Size += data[root2].Size;
        }
        else
        {
            data[root1].Root = root2;
            data[root2].Size += data[root1].Size;
        }
    }

    [[nodiscard]] bool addEdge(std::vector<NodeData> &data, size_t node1, size_t node2) const
    {
        const size_t root1 = getRoot(data, node1);
        const size_t root2 = getRoot(data, node2);
        if (root1 == root2)
            return false;
        merge(data, root1, root2);
        return true;
    }

    [[nodiscard]] size_t processEdges(std::vector<NodeData> &data, std::vector<std::vector<int>> const &edges, int processedEdgeType) const
    {
        size_t removedEdges = 0;
        for (std::vector<int> const &edge : edges)
        {
            if (edge[0] != processedEdgeType)
                continue;
            removedEdges += (addEdge(data, edge[1] - 1, edge[2] - 1) ? 0 : 1);
        }
        return removedEdges;
    }

    [[nodiscard]] bool canTraverse(std::vector<NodeData> const &data) const
    {
        size_t rootCount = 0;
        for (size_t node = 0; node < data.size(); ++node)
        {
            if (node == data[node].Root)
                ++rootCount;
        }
        return rootCount == 1;
    }
};

}

namespace RemoveMaxNumberOfEdgesTask
{

TEST(RemoveMaxNumberOfEdgesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxNumEdgesToRemove(4, {{3, 1, 2}, {3, 2, 3}, {1, 1, 3}, {1, 2, 4}, {1, 1, 2}, {2, 3, 4}}));
    ASSERT_EQ(0, solution.maxNumEdgesToRemove(4, {{3, 1, 2}, {3, 2, 3}, {1, 1, 4}, {2, 1, 4}}));
    ASSERT_EQ(-1, solution.maxNumEdgesToRemove(4, {{3, 2, 3}, {1, 1, 2}, {2, 3, 4}}));
}

}