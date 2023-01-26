#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findCheapestPrice(int n, std::vector<std::vector<int>> const &flights, int src, int dst, int k) const
    {
        std::vector<Node> nodes(n, Node());
        for (std::vector<int> const& flight : flights)
        {
            const size_t from = flight[0];
            const size_t to = flight[1];
            const int price = flight[2];
            nodes[from].Links.emplace_back(to, price);
        }
        std::vector<int> bestPrices(n, INT_MAX);
        size_t currentStep = 0;
        const size_t maxStep = k;
        std::queue<std::pair<size_t, int>> queue;
        queue.emplace(src, 0);
        bestPrices[src] = 0;
        while (!queue.empty() && (currentStep <= maxStep))
        {
            const size_t nextNodesSize = queue.size();
            for (size_t index = 0; index < nextNodesSize; ++index)
            {
                auto [currentNode, currentPrice] = queue.front();
                queue.pop();
                for (Link const &link : nodes[currentNode].Links)
                {
                    const int linkPrice = currentPrice + link.Price;
                    if (linkPrice < bestPrices[link.Node])
                    {
                        bestPrices[link.Node] = linkPrice;
                        queue.emplace(link.Node, linkPrice);
                    }
                }
            }
            ++currentStep;
        }
        return bestPrices[dst] == INT_MAX ? -1 : bestPrices[dst];
    }

private:
    struct Link
    {
        Link(size_t node, int price) : Node(node), Price(price)
        {
        }

        size_t Node;
        int Price;
    };

    struct Node
    {
        Node() = default;

        std::vector<Link> Links;
    };
};

}

namespace CheapestFlightsWithinKStopsTask
{

TEST(CheapestFlightsWithinKStopsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(700, solution.findCheapestPrice(4, {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}}, 0, 3, 1));
    ASSERT_EQ(200, solution.findCheapestPrice(3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 1));
    ASSERT_EQ(500, solution.findCheapestPrice(3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 0));
}

TEST(CheapestFlightsWithinKStopsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.findCheapestPrice(4, {{0, 1, 1}, {0, 2, 5}, {1, 2, 1}, {2, 3, 1}}, 0, 3, 1));
}

}