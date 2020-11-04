#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Course
{
    Course() : prerequisitesCount(0)
    {
    }

    int prerequisitesCount;
    std::vector<int> dependentCourses;
};

class Solution
{
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>> const &prerequisites) const
    {
        std::vector<Course> courses(numCourses);
        for (std::vector<int> const &prerequisite : prerequisites)
        {
            const int prerequisiteCourse = prerequisite[1];
            const int dependentCourse = prerequisite[0];
            ++courses[dependentCourse].prerequisitesCount;
            courses[prerequisiteCourse].dependentCourses.push_back(dependentCourse);
        }
        std::queue<int> independentCourses;
        for (size_t course = 0; course < courses.size(); ++course)
        {
            if (courses[course].prerequisitesCount == 0)
                independentCourses.push(static_cast<int>(course));
        }
        std::vector<int> topologicalSort;
        while (!independentCourses.empty())
        {
            int course = independentCourses.front();
            topologicalSort.push_back(course);
            for (int dependentCourse : courses[course].dependentCourses)
            {
                --courses[dependentCourse].prerequisitesCount;
                if (courses[dependentCourse].prerequisitesCount == 0)
                    independentCourses.push(dependentCourse);
            }
            independentCourses.pop();
        }
        return topologicalSort.size() == courses.size() ? topologicalSort : std::vector<int>();
    }
};

}

namespace CourseScheduleIITask
{

TEST(CourseScheduleIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1}), solution.findOrder(2, {{1, 0}}));
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3}), solution.findOrder(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}));
    ASSERT_EQ(std::vector<int>({0}), solution.findOrder(1, {}));
}

}