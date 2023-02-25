#include <list>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>> const &graph) const
    {
        std::vector<std::vector<int>> result;
        std::list<int> path({0});
        findPath(graph, 0, path, result);
        return result;
    }

private:
    void findPath(std::vector<std::vector<int>> const &graph, size_t currentNode, std::list<int> &path, std::vector<std::vector<int>> &result) const
    {
        if (currentNode == (graph.size() - 1))
        {
            result.emplace_back(path.begin(), path.end());
            return;
        }
        for (int neighbor : graph[currentNode])
        {
            path.push_back(neighbor);
            findPath(graph, neighbor, path, result);
            path.pop_back();
        }
    }
};

}

namespace AllPathsFromSourceToTargetTask
{

TEST(AllPathsFromSourceToTargetTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1, 3}, {0, 2, 3}}), solution.allPathsSourceTarget({{1, 2}, {3}, {3}, {}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 4}, {0, 3, 4}, {0, 1, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 4}}), solution.allPathsSourceTarget({{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1}}), solution.allPathsSourceTarget({{1}, {}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1, 2, 3}, {0, 2, 3}, {0, 3}}), solution.allPathsSourceTarget({{1, 2, 3}, {2}, {3}, {}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1, 2, 3}, {0, 3}}), solution.allPathsSourceTarget({{1, 3}, {2}, {3}, {}}));
}

}