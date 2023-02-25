#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Data
{
    Data(size_t n) : Visited(n, false), Depth(n, 0), Low(n, 0)
    {
    }

    std::vector<bool> Visited;
    std::vector<int> Depth;
    std::vector<int> Low;
};

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> criticalConnections(int n, std::vector<std::vector<int>> const &connections) const
    {
        std::vector<std::vector<int>> nodes(n, std::vector<int>());
        for (std::vector<int> const &connection : connections)
        {
            nodes[connection[0]].push_back(connection[1]);
            nodes[connection[1]].push_back(connection[0]);
        }
        Data data(n);
        std::vector<std::vector<int>> bridges;
        getBridges(0, 0, -1, nodes, data, bridges);
        return bridges;
    }

private:
    void getBridges(int node, int depth, int parent, std::vector<std::vector<int>> const &nodes, Data &data, std::vector<std::vector<int>> &bridges) const
    {
        data.Visited[node] = true;
        data.Depth[node] = depth;
        data.Low[node] = depth;
        for (int neighbour : nodes[node])
        {
            if (!data.Visited[neighbour])
            {
                getBridges(neighbour, depth + 1, node, nodes, data, bridges);
                data.Low[node] = std::min(data.Low[node], data.Low[neighbour]);
                if (data.Low[neighbour] > data.Depth[node])
                    bridges.push_back(std::vector<int>({node, neighbour}));
            }
            else if ((neighbour != parent) && (data.Depth[neighbour] < data.Depth[node]))
                data.Low[node] = std::min(data.Low[node], data.Depth[neighbour]);
        }
    }
};

}

namespace CriticalConnectionsInNetworkTask
{

TEST(CriticalConnectionsInNetworkTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 3}}), solution.criticalConnections(4, {{0, 1}, {1, 2}, {2, 0}, {1, 3}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1}}), solution.criticalConnections(2, {{0, 1}}));
}

}