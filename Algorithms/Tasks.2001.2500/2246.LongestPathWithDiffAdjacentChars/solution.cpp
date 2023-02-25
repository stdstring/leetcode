#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestPath(std::vector<int> const &parent, std::string const &s) const
    {
        std::vector<Node> nodes(parent.size(), Node());
        for (size_t index = 0; index < parent.size(); ++index)
        {
            nodes[index].Value = s[index];
            nodes[index].Parent = parent[index];
            if (parent[index] != -1)
                nodes[parent[index]].Children.push_back(index);
        }
        return static_cast<int>(calcLongestPath(nodes, 0).MaxPath);
    }

private:
    struct Node
    {
        Node() = default;

        char Value = '\0';
        int Parent = -1;
        std::vector<size_t> Children;
    };

    struct Result
    {
        Result(char lastValue, size_t maxBranch, size_t maxPath) : LastValue(lastValue), MaxBranch(maxBranch), MaxPath(maxPath)
        {
        }

        char LastValue;
        size_t MaxBranch;
        size_t MaxPath;
    };

    [[nodiscard]] Result calcLongestPath(std::vector<Node> const &nodes, size_t node) const
    {
        size_t maxPath = 1;
        std::vector<size_t> branches;
        for (const size_t child : nodes[node].Children)
        {
            Result childResult(calcLongestPath(nodes, child));
            maxPath = std::max(maxPath, childResult.MaxPath);
            if (childResult.LastValue != nodes[node].Value)
                branches.emplace_back(childResult.MaxBranch);
        }
        std::sort(branches.begin(), branches.end(), std::greater<>());
        const size_t maxBranch = 1 + (branches.empty() ? 0 : branches.front());
        maxPath = std::max(maxPath, maxBranch);
        if (branches.size() > 1)
            maxPath = std::max(maxPath, 1 + branches[0] + branches[1]);
        return {nodes[node].Value, maxBranch, maxPath};
    }
};

}

namespace LongestPathWithDiffAdjacentCharsTask
{

TEST(LongestPathWithDiffAdjacentCharsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.longestPath({-1, 0, 0, 1, 1, 2}, "abacbe"));
    ASSERT_EQ(3, solution.longestPath({-1, 0, 0, 0}, "aabc"));
}

}