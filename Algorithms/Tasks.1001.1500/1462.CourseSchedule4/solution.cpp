#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<bool> checkIfPrerequisite(int numCourses,
                                                        std::vector<std::vector<int>> const &prerequisites,
                                                        std::vector<std::vector<int>> const &queries) const
    {
        std::vector<std::vector<int>> coursesGraph(numCourses);
        for (std::vector<int> const& prerequisite : prerequisites)
            coursesGraph[prerequisite[0]].emplace_back(prerequisite[1]);
        std::vector<std::vector<bool>> isReachable(numCourses, std::vector<bool>(numCourses, false));
        for (int course = 0; course < numCourses; ++course)
            processCoursesGraph(coursesGraph, course, course, isReachable);
        std::vector<bool> result(queries.size(), false);
        for (size_t index = 0; index < queries.size(); ++index)
            result[index] = isReachable[queries[index][0]][queries[index][1]];
        return result;
    }

private:
    void processCoursesGraph(std::vector<std::vector<int>> const &coursesGraph,
                             int start,
                             int current,
                             std::vector<std::vector<bool>> &isReachable) const
    {
        if (isReachable[start][current])
            return;
        isReachable[start][current] = true;
        for (int next : coursesGraph[current])
            processCoursesGraph(coursesGraph, start, next, isReachable);
    }
};

}

namespace CourseSchedule4Task
{

TEST(CourseSchedule4TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<bool>({false, true}),
              solution.checkIfPrerequisite(2, {{1, 0}}, {{0, 1}, {1, 0}}));
    ASSERT_EQ(std::vector<bool>({false, false}),
              solution.checkIfPrerequisite(2, {}, {{1, 0}, {0, 1}}));
    ASSERT_EQ(std::vector<bool>({true, true}),
              solution.checkIfPrerequisite(3, {{1, 2}, {1, 0}, {2, 0}}, {{1, 0}, {1, 2}}));
}

}