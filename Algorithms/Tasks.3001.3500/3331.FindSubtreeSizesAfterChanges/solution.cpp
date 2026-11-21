#include <string>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findSubtreeSizes(std::vector<int> const &parent, std::string const &s) const
    {
        std::vector<std::vector<int>> nodes(generateNodes(parent));
        std::vector<int> usedLetter(AlphabetSize, -1);
        std::vector<int> updatedParent(parent.size(), -1);
        processString(0, -1, nodes, s, usedLetter, updatedParent);
        std::vector<std::vector<int>> updatedNodes(generateNodes(updatedParent));
        std::vector<int> result(parent.size(), 0);
        std::ignore = calcSubtreeSize(updatedNodes, 0, result);
        return result;
    }

private:
    static constexpr size_t AlphabetStart = 'a';
    static constexpr size_t AlphabetSize = 26;

    [[nodiscard]] std::vector<std::vector<int>> generateNodes(std::vector<int> const &parent) const
    {
        const int nodesCount = static_cast<int>(parent.size());
        std::vector<std::vector<int>> nodes(nodesCount);
        for (int node = 0; node < nodesCount; ++node)
        {
            if (parent[node] != -1)
                nodes[parent[node]].emplace_back(node);
        }
        return nodes;
    }

    void processString(int current,
                       int parent,
                       std::vector<std::vector<int>> const &nodes,
                       std::string const &s,
                       std::vector<int> &usedLetter,
                       std::vector<int> &updatedParent) const
    {
        const size_t currentChar = s[current] - AlphabetStart;
        const int prevUsedLetter = usedLetter[currentChar];
        updatedParent[current] = usedLetter[currentChar] != -1 ? usedLetter[currentChar] : parent;
        usedLetter[currentChar] = current;
        for (const int child : nodes[current])
            processString(child, current, nodes, s, usedLetter, updatedParent);
        usedLetter[currentChar] = prevUsedLetter;
    }

    [[nodiscard]] int calcSubtreeSize(std::vector<std::vector<int>> &nodes, int current, std::vector<int> &result) const
    {
        int currentSize = 1;
        for (const int child : nodes[current])
            currentSize += calcSubtreeSize(nodes, child, result);
        result[current] = currentSize;
        return currentSize;
    }
};

}

namespace FindSubtreeSizesAfterChangesTask
{

TEST(FindSubtreeSizesAfterChangesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({6, 3, 1, 1, 1, 1}), solution.findSubtreeSizes({-1, 0, 0, 1, 1, 1}, "abaabc"));
    ASSERT_EQ(std::vector<int>({5, 2, 1, 1, 1}), solution.findSubtreeSizes({-1, 0, 4, 0, 1}, "abbba"));
}

}
