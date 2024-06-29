#include <bitset>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> getAncestors(int n, std::vector<std::vector<int>> const &edges) const
    {
        // init node data
        std::vector<NodeData> nodes(n);
        for (std::vector<int> const &edge : edges)
        {
            nodes[edge[0]].outgoing.emplace_back(edge[1]);
            nodes[edge[1]].hasIncoming = true;
        }
        // bfs process
        std::queue<int> bfsNodes;
        std::vector<bool> processedNodes(n, false);
        for (int node = 0; node < n; ++node)
        {
            if (!nodes[node].hasIncoming)
            {
                bfsNodes.emplace(node);
                processedNodes[node] = true;
            }
        }
        while (!bfsNodes.empty())
        {
            const int current = bfsNodes.front();
            bfsNodes.pop();
            processedNodes[current] = false;
            for (const int next : nodes[current].outgoing)
            {
                nodes[next].ancestors |= nodes[current].ancestors;
                nodes[next].ancestors.set(current, true);
                if (!processedNodes[next])
                {
                    processedNodes[next] = true;
                    bfsNodes.emplace(next);
                }
            }
        }
        // extract result
        std::vector<std::vector<int>> result(n);
        for (int node = 0; node < n; ++node)
        {
            for (int next = 0; next < n; ++next)
            {
                if (nodes[node].ancestors[next])
                    result[node].emplace_back(next);
            }
        }
        return result;
    }

private:
    static constexpr size_t MaxNodeCount = 1000;

    struct NodeData
    {
        bool hasIncoming = false;
        std::vector<int> outgoing;
        std::bitset<MaxNodeCount> ancestors;
    };
};

}

namespace AllAncestorsOfNodeInDAGTask
{

TEST(AllAncestorsOfNodeInDAGTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{}, {}, {}, {0, 1}, {0, 2}, {0, 1, 3}, {0, 1, 2, 3, 4}, {0, 1, 2, 3}}),
              solution.getAncestors(8, {{0, 3}, {0, 4}, {1, 3}, {2, 4}, {2, 7}, {3, 5}, {3, 6}, {3, 7}, {4, 6}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{}, {0}, {0, 1}, {0, 1, 2}, {0, 1, 2, 3}}),
              solution.getAncestors(5, {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}}));
}

}