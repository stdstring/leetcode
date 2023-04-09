#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestPathValue(std::string const &colors, std::vector<std::vector<int>> const &edges) const
    {
        std::vector<Node> nodes(colors.size(), Node());
        for (size_t index = 0; index < nodes.size(); ++index)
            nodes[index].Value = colors[index] - AlphabetStart;
        for (std::vector<int> const & edge : edges)
        {
            const size_t startNode = edge[0];
            const size_t finishNode = edge[1];
            nodes[startNode].Links.emplace_back(finishNode);
        }
        for (size_t index = 0; index < nodes.size(); ++index)
        {
            if (nodes[index].VisitColor == VisitColor::White)
            {
                if (!processNodes(nodes, index))
                    return -1;
            }
        }
        int largestValue = 0;
        for (Node const &node : nodes)
        {
            for (int charCount : node.PathsLetterData)
                largestValue = std::max(largestValue, charCount);
        }
        return largestValue;
    }

private:
    constexpr static size_t AlphabetSize = 26;
    constexpr static size_t AlphabetStart = 'a';

    enum class VisitColor { White, Gray, Black };

    struct Node
    {
        Node() : Value(AlphabetSize), VisitColor(VisitColor::White), PathsLetterData(AlphabetSize, 0)
        {
        }

        size_t Value;
        std::vector<size_t> Links;
        VisitColor VisitColor;
        std::vector<int> PathsLetterData;
    };

    [[nodiscard]] bool processNodes(std::vector<Node> &nodes, size_t current) const
    {
        if (nodes[current].VisitColor == VisitColor::Gray)
            return false;
        if (nodes[current].VisitColor == VisitColor::Black)
            return true;
        nodes[current].VisitColor = VisitColor::Gray;
        for (const size_t link : nodes[current].Links)
        {
            if (!processNodes(nodes, link))
                return false;
            mergePathsLetterData(nodes[link].PathsLetterData, nodes[current].PathsLetterData);
        }
        ++nodes[current].PathsLetterData[nodes[current].Value];
        nodes[current].VisitColor = VisitColor::Black;
        return true;
    }

    void mergePathsLetterData(std::vector<int> const &source, std::vector<int> &dest) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
            dest[index] = std::max(dest[index], source[index]);
    }
};

}

namespace LargestColorValueInDirectedGraphTask
{

TEST(LargestColorValueInDirectedGraphTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.largestPathValue("abaca", {{0, 1}, {0, 2}, {2, 3}, {3, 4}}));
    ASSERT_EQ(-1, solution.largestPathValue("a", {{0, 0}}));
}

TEST(LargestColorValueInDirectedGraphTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.largestPathValue("hhqhuqhqff", {{0, 1}, {0, 2}, {2, 3}, {3, 4}, {3, 5}, {5, 6}, {2, 7}, {6, 7}, {7, 8}, {3, 8}, {5, 8}, {8, 9}, {3, 9}, {6, 9}}));
}

}