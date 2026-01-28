#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minCost(int n, std::vector<std::vector<int>> const &edges) const
    {
        std::vector<std::vector<Link>> nodes(n);
        for (std::vector<int> const &edge : edges)
        {
            const int nodeFrom = edge[0];
            const int nodeTo = edge[1];
            const int weight = edge[2];
            nodes[nodeFrom].emplace_back(nodeTo, weight);
            nodes[nodeTo].emplace_back(nodeFrom, 2 * weight);
        }
        // Dijkstra's algorithm
        std::vector<int> costs(n, INT_MAX);
        // weight, node
        typedef std::pair<int, int> TQueueEntry;
        auto cmp = [](TQueueEntry const &left, TQueueEntry const &right)
        {
            return left.first > right.first;
        };
        std::priority_queue<TQueueEntry, std::vector<TQueueEntry>, decltype(cmp)> queue(cmp);
        queue.emplace(0, 0);
        while (!queue.empty())
        {
            auto [weight, current] = queue.top();
            queue.pop();
            if (costs[current] <= weight)
                continue;
            if (current == (n - 1))
                return weight;
            costs[current] = weight;
            for (Link const &link : nodes[current])
            {
                const int linkWeight = weight + link.Weight;
                if (linkWeight < costs[link.NodeTo])
                    queue.emplace(linkWeight, link.NodeTo);
            }
        }
        return -1;
    }

private:
    struct Link
    {
        Link(int nodeTo, int weight) : NodeTo(nodeTo), Weight(weight)
        {
        }
        int NodeTo;
        int Weight;
    };
};

}

namespace MinCostPathWithEdgeReversalsTask
{

TEST(MinCostPathWithEdgeReversalsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minCost(4, {{0, 1, 3}, {3, 1, 1}, {2, 3, 4}, {0, 2, 2}}));
    ASSERT_EQ(3, solution.minCost(4, {{0, 2, 1}, {2, 1, 1}, {1, 3, 1}, {2, 3, 3}}));
}

}