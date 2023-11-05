#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countHighestScoreNodes(std::vector<int> const &parents) const
    {
        const int nodeCount = static_cast<int>(parents.size());
        std::vector<std::pair<int, int>> children(nodeCount, {-1, -1});
        // node == 0 - always root node
        for (int node = 1; node < nodeCount; ++node)
        {
            const int parent = parents[node];
            (children[parent].first == -1 ? children[parent].first : children[parent].second) = node;
        }
        return countHighestScoreNodes(0, nodeCount, children).BestScoreCount;
    }

private:
    struct NodeData
    {
        NodeData(long long bestScore, int bestScoreCount, int subtreeSize) :
            BestScore(bestScore),
            BestScoreCount(bestScoreCount),
            SubtreeSize(subtreeSize)
        {
        }

        long long BestScore;
        int BestScoreCount;
        int SubtreeSize;
    };

    NodeData countHighestScoreNodes(int node, int nodeCount, std::vector<std::pair<int, int>> const &children) const
    {
        long long bestScore = 0;
        int bestScoreCount = 0;
        int subtreeSize = 1;
        long long product = 1;
        if (children[node].first != -1)
        {
            const NodeData leftData(countHighestScoreNodes(children[node].first, nodeCount, children));
            product *= leftData.SubtreeSize;
            subtreeSize += leftData.SubtreeSize;
            if (bestScore < leftData.BestScore)
            {
                bestScore = leftData.BestScore;
                bestScoreCount = leftData.BestScoreCount;
            }
            else if (bestScore == leftData.BestScore)
                bestScoreCount += leftData.BestScoreCount;
        }
        if (children[node].second != -1)
        {
            const NodeData rightData(countHighestScoreNodes(children[node].second, nodeCount, children));
            product *= rightData.SubtreeSize;
            subtreeSize += rightData.SubtreeSize;
            if (bestScore < rightData.BestScore)
            {
                bestScore = rightData.BestScore;
                bestScoreCount = rightData.BestScoreCount;
            }
            else if (bestScore == rightData.BestScore)
                bestScoreCount += rightData.BestScoreCount;
        }
        if ((nodeCount - subtreeSize) > 0)
            product *= (nodeCount - subtreeSize);
        if (bestScore < product)
        {
            bestScore = product;
            bestScoreCount = 1;
        }
        else if (bestScore == product)
            ++bestScoreCount;
        return NodeData(bestScore, bestScoreCount, subtreeSize);
    }
};

}

namespace CountNodesWithHighestScoreTask
{

TEST(CountNodesWithHighestScoreTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countHighestScoreNodes({-1, 2, 0, 2, 0}));
    ASSERT_EQ(2, solution.countHighestScoreNodes({-1, 2, 0}));
}

TEST(CountNodesWithHighestScoreTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.countHighestScoreNodes({-1, 2, 4, 0, 0, 4, 2}));
}

}