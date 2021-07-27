#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numBusesToDestination(std::vector<std::vector<int>> const &routes, int source, int target) const
    {
        if (source == target)
            return 0;
        // create graph
        std::unordered_map<int, std::vector<size_t>> stopRoutesMap;
        for (size_t index = 0; index < routes.size(); ++index)
        {
            for (int stop : routes[index])
                stopRoutesMap[stop].push_back(index);
        }
        std::vector<std::vector<size_t>> routeGraph(routes.size());
        for (auto const &entry : stopRoutesMap)
        {
            for (size_t fromIndex = 0; fromIndex < entry.second.size(); ++fromIndex)
            {
                for (size_t toIndex = fromIndex + 1; toIndex < entry.second.size(); ++toIndex)
                {
                    routeGraph[entry.second[fromIndex]].push_back(entry.second[toIndex]);
                    routeGraph[entry.second[toIndex]].push_back(entry.second[fromIndex]);
                }
            }
        }
        const size_t startNode = addSpecialNode(stopRoutesMap, routeGraph, source);
        const size_t endNode = addSpecialNode(stopRoutesMap, routeGraph, target);
        // BFS
        std::queue<size_t> queue;
        std::vector<int> distances(routeGraph.size(), NoPathValue);
        queue.push(startNode);
        distances[startNode] = 0;
        while (!queue.empty())
        {
            for (size_t link : routeGraph[queue.front()])
            {
                if (distances[link] == NoPathValue)
                {
                    distances[link] = distances[queue.front()] + 1;
                    queue.push(link);
                }
            }
            queue.pop();
        }
        return distances[endNode] == NoPathValue ? -1 : distances[endNode] - 1;
    }

private:
    static constexpr size_t NoPathValue = INT_MAX;

    size_t addSpecialNode(std::unordered_map<int, std::vector<size_t>> const &stopRoutesMap, std::vector<std::vector<size_t>> &routeGraph, int busStop) const
    {
        routeGraph.push_back(stopRoutesMap.at(busStop));
        const size_t node = routeGraph.size() - 1;
        for (size_t link : routeGraph.back())
            routeGraph[link].push_back(node);
        return node;
    }
};

}

namespace BusRoutesTask
{

TEST(BusRoutesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.numBusesToDestination({{1, 2, 7}, {3, 6, 7}}, 1, 6));
    ASSERT_EQ(-1, solution.numBusesToDestination({{7, 12}, {4, 5, 15}, {6}, {15, 19}, {9, 12, 13}}, 15, 12));
}

TEST(BusRoutesTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.numBusesToDestination({{1, 7}, {3, 5}}, 5, 5));
}

}
