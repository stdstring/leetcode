#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> placedCoins(std::vector<std::vector<int>> const &edges, std::vector<int> const &cost) const
    {
        const size_t nodeCount = cost.size();
        std::vector<std::vector<int>> nodes(nodeCount);
        for (std::vector<int> const &edge : edges)
        {
            nodes[edge[0]].emplace_back(edge[1]);
            nodes[edge[1]].emplace_back(edge[0]);
        }
        std::vector<long long> coins(nodeCount, 0);
        processTree(nodes, 0, -1, cost, coins);
        return coins;
    }

private:
    struct NodeData
    {
        NodeData(std::vector<int> largestNumbers, std::vector<int> smallestNumbers) :
            LargestNumbers(std::move(largestNumbers)),
            SmallestNumbers(std::move(smallestNumbers))
        {
        }

        std::vector<int> LargestNumbers;
        std::vector<int> SmallestNumbers;
    };

    NodeData processTree(std::vector<std::vector<int>> const &nodes, int current, int parent, std::vector<int> const &cost, std::vector<long long> &coins) const
    {
        std::vector<int> largestNumbers({cost[current]});
        std::vector<int> smallestNumbers({cost[current]});
        for (const int neighbor : nodes[current])
        {
            if (neighbor == parent)
                continue;
            NodeData data(processTree(nodes, neighbor, current, cost, coins));
            std::ranges::copy(data.LargestNumbers, std::back_inserter(largestNumbers));
            std::ranges::copy(data.SmallestNumbers, std::back_inserter(smallestNumbers));
        }
        std::ranges::sort(largestNumbers, std::greater<int>());
        std::ranges::sort(smallestNumbers);
        while (largestNumbers.size() > 3)
            largestNumbers.pop_back();
        while (smallestNumbers.size() > 3)
            smallestNumbers.pop_back();
        if (largestNumbers.size() < 3)
            coins[current] = 1;
        else
        {
            const long long coin1 = 1LL * largestNumbers[0] * largestNumbers[1] * largestNumbers[2];
            const long long coin2 = 1LL * largestNumbers[0] * smallestNumbers[0] * smallestNumbers[1];
            const long long coin = std::max(coin1, coin2);
            coins[current] = coin < 0 ? 0 : coin;
        }
        return NodeData(largestNumbers, smallestNumbers);
    }
};

}

namespace FindNumberCoinsToPlaceInTreeNodesTask
{

TEST(FindNumberCoinsToPlaceInTreeNodesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({120, 1, 1, 1, 1, 1}),
              solution.placedCoins({{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}}, {1, 2, 3, 4, 5, 6}));
    ASSERT_EQ(std::vector<long long>({280, 140, 32, 1, 1, 1, 1, 1, 1}),
              solution.placedCoins({{0, 1}, {0, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 6}, {2, 7}, {2, 8}}, {1, 4, 2, 3, 5, 7, 8, -4, 2}));
    ASSERT_EQ(std::vector<long long>({0, 1, 1}), solution.placedCoins({{0, 1}, {0, 2}}, {1, 2, -2}));
}

}