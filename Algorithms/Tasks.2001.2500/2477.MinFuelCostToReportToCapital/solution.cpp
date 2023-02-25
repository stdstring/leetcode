#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumFuelCost(std::vector<std::vector<int>> const &roads, int seats) const
    {
        std::vector<Node> graph(roads.size() + 1, Node());
        for (std::vector<int> const &road : roads)
        {
            graph[road[0]].Neighbors.push_back(road[1]);
            graph[road[1]].Neighbors.push_back(road[0]);
        }
        return processTree(graph, 0, static_cast<int>(graph.size()), seats).FuelCount;
    }

private:
    struct Node
    {
        Node() = default;

        std::vector<int> Neighbors;
    };

    struct Result
    {
        Result(int peopleCount, long long fuelCount) : PeopleCount(peopleCount), FuelCount(fuelCount)
        {
        }

        int PeopleCount;
        long long FuelCount;
    };

    [[nodiscard]] Result processTree(std::vector<Node> const &graph, int current, int parent, int seats) const
    {
        Result result(1, 0);
        for (const int neighbor : graph[current].Neighbors)
        {
            if (neighbor == parent)
                continue;
            const Result neighborResult(processTree(graph, neighbor, current, seats));
            result.PeopleCount += neighborResult.PeopleCount;
            result.FuelCount += neighborResult.FuelCount;
            result.FuelCount += (neighborResult.PeopleCount / seats + (neighborResult.PeopleCount % seats == 0 ? 0 : 1));
        }
        return result;
    }
};

}

namespace MinFuelCostToReportToCapitalTask
{

TEST(MinFuelCostToReportToCapitalTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumFuelCost({{0, 1}, {0, 2}, {0, 3}}, 5));
    ASSERT_EQ(7, solution.minimumFuelCost({{3, 1}, {3, 2}, {1, 0}, {0, 4}, {0, 5}, {4, 6}}, 2));
    ASSERT_EQ(0, solution.minimumFuelCost({}, 1));
}

}