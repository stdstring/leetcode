#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> buildMatrix(int k, std::vector<std::vector<int>> const &rowConditions, std::vector<std::vector<int>> const &colConditions) const
    {
        const std::vector<std::vector<int>> rowConditionGraph(createConditionGraph(k, rowConditions));
        const std::vector<std::vector<int>> columnConditionGraph(createConditionGraph(k, colConditions));
        const std::vector<int> rowSortedNumbers(generateSortedNumbers(k, rowConditionGraph));
        if (rowSortedNumbers.empty())
            return {};
        const std::vector<int> columnSortedNumbers(generateSortedNumbers(k, columnConditionGraph));
        if (columnSortedNumbers.empty())
            return {};
        std::vector<std::vector<int>> result(k, std::vector<int>(k, 0));
        std::vector<size_t> numberRowPositions(k + 1, 0);
        for (size_t row = 0; row < rowSortedNumbers.size(); ++row)
            numberRowPositions[rowSortedNumbers[row]] = row;
        for (size_t column = 0; column < columnSortedNumbers.size(); ++column)
        {
            const int number = columnSortedNumbers[column];
            result[numberRowPositions[number]][column] = number;
        }
        return result;
    }

private:
    enum class NodeColor
    {
        White = 0,
        Gray = 1,
        Black = 2
    };

    [[nodiscard]] std::vector<std::vector<int>> createConditionGraph(int k, std::vector<std::vector<int>> const &conditions) const
    {
        std::vector<std::vector<int>> conditionGraph(k);
        for (std::vector<int> const &condition : conditions)
        {
            const int before = condition[0] - 1;
            const int after = condition[1] - 1;
            conditionGraph[before].emplace_back(after);
        }
        return conditionGraph;
    }

    [[nodiscard]] std::vector<int> generateSortedNumbers(int k, std::vector<std::vector<int>> const &graph) const
    {
        std::vector<NodeColor> nodesState(k, NodeColor::White);
        std::vector<int> sortedNumbers;
        for (int node = 0; node < k; ++node)
        {
            if (!topologicalSort(node, graph, nodesState, sortedNumbers))
                return {};
        }
        std::ranges::reverse(sortedNumbers);
        return sortedNumbers;
    }

    [[nodiscard]] bool topologicalSort(int node, std::vector<std::vector<int>> const &graph, std::vector<NodeColor> &nodesState, std::vector<int> &sortedNumbers) const
    {
        if (nodesState[node] == NodeColor::Black)
            return true;
        if (nodesState[node] == NodeColor::Gray)
            return false;
        const int number = node + 1;
        nodesState[node] = NodeColor::Gray;
        for (const int neighbor : graph[node])
        {
            if (!topologicalSort(neighbor, graph, nodesState, sortedNumbers))
                return false;
        }
        nodesState[node] = NodeColor::Black;
        sortedNumbers.emplace_back(number);
        return true;
    }
};

}

namespace BuildMatrixWithConditionsTask
{

TEST(BuildMatrixWithConditionsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 0, 0}, {0, 0, 1}, {0, 2, 0}}), solution.buildMatrix(3, {{1, 2}, {3, 2}}, {{2, 1}, {3, 2}}));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.buildMatrix(3, {{1, 2}, {2, 3}, {3, 1}, {2, 3}}, {{2, 1}}));
}

}