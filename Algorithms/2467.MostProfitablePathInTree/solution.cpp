#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"


namespace
{

class Solution
{
public:
    [[nodiscard]] int mostProfitablePath(std::vector<std::vector<int>> const &edges, int bob, std::vector<int> const &amount) const
    {
        std::unordered_map<int, Node> nodes;
        for (std::vector<int> edge : edges)
        {
            nodes[edge[0]].Links.emplace_back(edge[1]);
            nodes[edge[1]].Links.emplace_back(edge[0]);
        }
        for (int node = 0; node < static_cast<int>(amount.size()); ++node)
            nodes[node].Amount = amount[node];
        fixTreeStructure(0, nodes);
        for (int bobStep = 0; bob != -1; ++bobStep, bob = nodes[bob].Parent)
            nodes[bob].BobStep = bobStep;
        return calcMaxIncome(0, 0, 0, nodes);
    }

private:
    struct Node
    {
        Node() : Parent(-1), Amount(0), BobStep(-1)
        {
        }

        int Parent;
        std::vector<int> Links;
        int Amount;
        int BobStep;
    };

    void fixTreeStructure(int current, std::unordered_map<int, Node> &nodes) const
    {
        for (int next : nodes[current].Links)
        {
            if (nodes[current].Parent != next)
            {
                nodes[next].Parent = current;
                fixTreeStructure(next, nodes);
            }
        }
    }

    [[nodiscard]] int calcMaxIncome(int current, int prevIncome, int currentStep, std::unordered_map<int, Node> const &nodes) const
    {
        int currentIncome = prevIncome;
        if ((nodes.at(current).BobStep == -1) || (currentStep < nodes.at(current).BobStep))
            currentIncome += nodes.at(current).Amount;
        if (nodes.at(current).BobStep == currentStep)
            currentIncome += (nodes.at(current).Amount / 2);
        if ((nodes.at(current).Links.size() == 1) && (nodes.at(current).Parent != -1))
            return currentIncome;
        int result = INT_MIN;
        for (const int next : nodes.at(current).Links)
        {
            if (next != nodes.at(current).Parent)
                result = std::max(result, calcMaxIncome(next, currentIncome, currentStep + 1, nodes));
        }
        return result;
    }
};

}

namespace MostProfitablePathInTreeTask
{

TEST(MostProfitablePathInTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.mostProfitablePath({{0, 1}, {1, 2}, {1, 3}, {3, 4}}, 3, {-2, 4, 2, -4, 6}));
    ASSERT_EQ(-7280, solution.mostProfitablePath({{0, 1}}, 1, {-7280, 2350}));
}

}