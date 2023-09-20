#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int edgeScore(std::vector<int> const &edges) const
    {
        const int nodeCount = static_cast<int>(edges.size());
        int bestNode = 0;
        long long bestLabelSum = 0;
        std::unordered_map<int, long long> nodeScoreMap;
        for (int node = 0; node < nodeCount; ++node)
        {
            auto iterator = nodeScoreMap.find(edges[node]);
            if (iterator == nodeScoreMap.end())
                iterator = nodeScoreMap.emplace(edges[node], 0).first;
            iterator->second += node;
            if ((bestLabelSum < iterator->second) || ((bestLabelSum == iterator->second) && (edges[node] < bestNode)))
            {
                bestNode = edges[node];
                bestLabelSum = iterator->second;
            }
        }
        return bestNode;
    }
};

}

namespace NodeWithHighestEdgeScoreTask
{

TEST(NodeWithHighestEdgeScoreTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.edgeScore({1, 0, 0, 0, 0, 7, 7, 5}));
    ASSERT_EQ(0, solution.edgeScore({2, 0, 0, 2}));
}

}