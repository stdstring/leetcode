#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool possibleBipartition(int n, std::vector<std::vector<int>> const &dislikes) const
    {
        std::vector<std::vector<size_t>> graph(n, std::vector<size_t>());
        for (std::vector<int> const &dislike : dislikes)
        {
            graph[dislike[0] - 1].emplace_back(dislike[1] - 1);
            graph[dislike[1] - 1].emplace_back(dislike[0] - 1);
        }
        std::vector<Color> nodeColors(n, Color::Undefined);
        for (size_t index = 0; index < graph.size(); ++index)
        {
            if (nodeColors[index] != Color::Undefined)
                continue;
            std::queue<size_t> queue;
            queue.push(index);
            nodeColors[index] = Color::Red;
            while (!queue.empty())
            {
                const size_t current = queue.front();
                queue.pop();
                for (size_t neighbor : graph[current])
                {
                    if (nodeColors[current] == nodeColors[neighbor])
                        return false;
                    if (nodeColors[neighbor] == Color::Undefined)
                    {
                        nodeColors[neighbor] = nodeColors[current] == Color::Red ? Color::Blue : Color::Red;
                        queue.push(neighbor);
                    }
                }
            }
        }
        return true;
    }

private:
    enum class Color {Undefined, Red, Blue};
};

}

namespace PossibleBipartitionTask
{

TEST(PossibleBipartitionTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.possibleBipartition(4, {{1, 2}, {1, 3}, {2, 4}}));
    ASSERT_EQ(false, solution.possibleBipartition(3, {{1, 2}, {1, 3}, {2, 3}}));
    ASSERT_EQ(false, solution.possibleBipartition(5, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 5}}));
}

TEST(PossibleBipartitionTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.possibleBipartition(50, {{11, 18}, {18, 29}, {3, 29}}));
    ASSERT_EQ(true, solution.possibleBipartition(8, {{3, 5}, {5, 7}, {1, 7}}));
}

}