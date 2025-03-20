#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> minimumCost(int n, std::vector<std::vector<int>> const &edges, std::vector<std::vector<int>> const &query) const
    {
        std::vector<std::vector<Link>> nodes(n);
        for (std::vector<int> const &edge : edges)
        {
            nodes[edge[0]].emplace_back(edge[1], edge[2]);
            nodes[edge[1]].emplace_back(edge[0], edge[2]);
        }
        std::vector<int> groupLeaders(n, -1);
        std::vector<int> groupValues(n, INT_MAX);
        for (int node = 0; node < n; ++node)
        {
            if (groupLeaders[node] == -1)
                processGroup(node, node, nodes, groupLeaders, groupValues);
        }
        std::vector<int> result(query.size(), -1);
        for (size_t index = 0; index < query.size(); ++index)
        {
            const int fromNode = query[index][0];
            const int toNode = query[index][1];
            result[index] = (groupLeaders[fromNode] == groupLeaders[toNode]) ? groupValues[groupLeaders[fromNode]] : -1;
        }
        return result;
    }

private:
    struct Link
    {
        Link(int toNode, int weight) : ToNode(toNode), Weight(weight)
        {
        }
        int ToNode;
        int Weight;
    };

    void processGroup(int leader, int current, std::vector<std::vector<Link>> const &nodes, std::vector<int> &groupLeaders, std::vector<int> &groupValues) const
    {
        groupLeaders[current] = leader;
        for (Link const &link : nodes[current])
        {
            groupValues[leader] &= link.Weight;
            if (groupLeaders[link.ToNode] == -1)
                processGroup(leader, link.ToNode, nodes, groupLeaders, groupValues);
        }
    }
};

}

namespace MinCostWalkInWeightedGraphTask
{

TEST(MinCostWalkInWeightedGraphTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, -1}), solution.minimumCost(5, {{0, 1, 7}, {1, 3, 7}, {1, 2, 1}}, {{0, 3}, {3, 4}}));
    ASSERT_EQ(std::vector<int>({0}), solution.minimumCost(3, {{0, 2, 7}, {0, 1, 15}, {1, 2, 6}, {1, 2, 1}}, {{1, 2}}));
}

}