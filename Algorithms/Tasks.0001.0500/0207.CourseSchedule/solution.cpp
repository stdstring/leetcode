#include <vector>

#include "gtest/gtest.h"

namespace
{

enum Color { WHITE, GRAY, BLACK };

class Solution
{
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>> const &prerequisites) const
    {
        std::vector<std::vector<int>> graph;
        std::vector<Color> verticesColors;
        for (int vertex = 0; vertex < numCourses; ++vertex)
        {
            graph.emplace_back();
            verticesColors.push_back(Color::WHITE);
        }
        for (std::vector<int> const &prerequisite : prerequisites)
            graph[prerequisite[0]].push_back(prerequisite[1]);
        for (int vertex = 0; vertex < numCourses; ++vertex)
        {
            if (verticesColors[vertex] == Color::WHITE)
            {
                if (hasCycle(graph, vertex, verticesColors))
                    return false;
            }
        }
        return true;
    }

private:
    bool hasCycle(std::vector<std::vector<int>> const &graph, int start, std::vector<Color> &verticesColors) const
    {
        if (verticesColors[start] == Color::BLACK)
            return false;
        if (verticesColors[start] == Color::GRAY)
            return true;
        verticesColors[start] = Color::GRAY;
        for (int link : graph[start])
        {
            if (hasCycle(graph, link, verticesColors))
                return true;
        }
        verticesColors[start] = Color::BLACK;
        return false;
    }
};

}

namespace CourseScheduleTask
{

TEST(CourseScheduleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canFinish(2, {{1, 0}}));
    ASSERT_EQ(false, solution.canFinish(2, {{1, 0}, {0, 1}}));
}

TEST(CourseScheduleTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canFinish(3, {{0, 1}, {0, 2}, {1, 2}}));
    ASSERT_EQ(true, solution.canFinish(7, {{1, 0}, {0, 3}, {0, 2}, {3, 2}, {2, 5}, {4, 5}, {5, 6}, {2, 4}}));
}

}