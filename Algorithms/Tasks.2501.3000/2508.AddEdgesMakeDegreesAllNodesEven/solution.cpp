#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isPossible(int n, std::vector<std::vector<int>> const &edges) const
    {
        std::vector<std::unordered_set<int>> nodes(n);
        for (std::vector<int> const &edge : edges)
        {
            int firstNode = edge[0] - 1;
            int secondNode = edge[1] - 1;
            nodes[firstNode].emplace(secondNode);
            nodes[secondNode].emplace(firstNode);
        }
        // you can add at most two additional edges (possibly none) => max possible nodes with odd degree is 4
        constexpr size_t maxPossibleOddDegreeNodes = 4;
        std::vector<int> oddDegreeNodes;
        for (int node = 0; node < n; ++node)
        {
            if ((nodes[node].size() % 2) != 0)
                oddDegreeNodes.emplace_back(node);
            if (oddDegreeNodes.size() > maxPossibleOddDegreeNodes)
                return false;
        }
        switch (oddDegreeNodes.size())
        {
        case 0:
            return true;
        case 2:
            return isPossible(n, nodes, oddDegreeNodes[0], oddDegreeNodes[1]);
        case 4:
        {
            const int node1 = oddDegreeNodes[0];
            const int node2 = oddDegreeNodes[1];
            const int node3 = oddDegreeNodes[2];
            const int node4 = oddDegreeNodes[3];
            // pairs: 1-2 + 3-4, 1-3 + 2-4, 1-4 + 2-3
            return (!nodes[node1].contains(node2) && !nodes[node3].contains(node4)) ||
                   (!nodes[node1].contains(node3) && !nodes[node2].contains(node4)) ||
                   (!nodes[node1].contains(node4) && !nodes[node2].contains(node3));
        }
        default:
            return false;
        }
    }

private:
    [[nodiscard]] bool isPossible(int n, std::vector<std::unordered_set<int>> const &nodes, int node1, int node2) const
    {
        if (!nodes[node1].contains(node2))
            return true;
        for (int node = 0; node < n; ++node)
        {
            if ((node == node1) || (node == node2))
                continue;
            if (!nodes[node].contains(node1) && !nodes[node].contains(node2))
                return true;
        }
        return false;
    }
};

}

namespace AddEdgesMakeDegreesAllNodesEvenTask
{

TEST(AddEdgesMakeDegreesAllNodesEvenTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isPossible(5, {{1, 2}, {2, 3}, {3, 4}, {4, 2}, {1, 4}, {2, 5}}));
    ASSERT_EQ(true, solution.isPossible(4, {{1, 2}, {3, 4}}));
    ASSERT_EQ(false, solution.isPossible(4, {{1, 2}, {1, 3}, {1, 4}}));
}

TEST(AddEdgesMakeDegreesAllNodesEvenTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isPossible(6, {{1, 2}, {1, 3}, {1, 4}, {4, 5}, {5, 6}}));
    ASSERT_EQ(false, solution.isPossible(4, {{1, 2}, {2, 3}, {2, 4}, {3, 4}}));
}

}