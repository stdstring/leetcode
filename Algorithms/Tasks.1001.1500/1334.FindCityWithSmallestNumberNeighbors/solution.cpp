#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findTheCity(int n, std::vector<std::vector<int>> const &edges, int distanceThreshold) const
    {
        std::vector<std::vector<Link>> graph(n);
        for (std::vector<int> const &edge : edges)
        {
            const int fromNode = edge[0];
            const int toNode = edge[1];
            const int weight = edge[2];
            graph[fromNode].emplace_back(toNode, weight);
            graph[toNode].emplace_back(fromNode, weight);
        }
        int bestCity = 0;
        size_t bestCityValue = INT_MAX;
        for (int city = 0; city < n; ++city)
        {
            std::vector<int> distances(calcDistances(n, graph, city));
            const size_t currentCityValue = std::ranges::count_if(distances, [distanceThreshold](int distance) { return distance <= distanceThreshold; });
            if (currentCityValue <= bestCityValue)
            {
                bestCity = city;
                bestCityValue = currentCityValue;
            }
        }
        return bestCity;
    }

private:
    struct Link
    {
        Link(int node, int weight) : Node(node), Weight(weight)
        {
        }
        int Node;
        int Weight;
    };

    struct City
    {
        City(int node, int distance) : Node(node), Distance(distance)
        {
        }
        int Node;
        int Distance;
    };

    [[nodiscard]] std::vector<int> calcDistances(int n, std::vector<std::vector<Link>> const &graph, int startCity) const
    {
        std::vector<int> distances(n, INT_MAX);
        std::vector<bool> processed(n, false);
        distances[startCity] = 0;
        auto cmp = [](City const &left, City const &right) { return left.Distance > right.Distance; };
        std::priority_queue<City, std::vector<City>, decltype(cmp)> cityQueue(cmp);
        cityQueue.emplace(startCity, 0);
        while (!cityQueue.empty())
        {
            const City current(cityQueue.top());
            cityQueue.pop();
            if (processed[current.Node])
                continue;
            processed[current.Node] = true;
            for (Link const &link : graph[current.Node])
            {
                if (processed[link.Node])
                    continue;
                if ((current.Distance + link.Weight) < distances[link.Node])
                {
                    distances[link.Node] = current.Distance + link.Weight;
                    cityQueue.emplace(link.Node, current.Distance + link.Weight);
                }
            }
        }
        return distances;
    }
};

}

namespace FindCityWithSmallestNumberNeighborsTask
{

TEST(FindCityWithSmallestNumberNeighborsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.findTheCity(4, {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}}, 4));
    ASSERT_EQ(0, solution.findTheCity(5, {{0, 1, 2}, {0, 4, 8}, {1, 2, 3}, {1, 4, 2}, {2, 3, 1}, {3, 4, 1}}, 2));
}

}