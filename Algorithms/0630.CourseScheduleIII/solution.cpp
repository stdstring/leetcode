#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int scheduleCourse(std::vector<std::vector<int>> const &courses) const
    {
        std::vector<std::vector<int>> sortedCourses(courses);
        std::sort(sortedCourses.begin(), sortedCourses.end(), [](std::vector<int> const &l, std::vector<int> const &r){ return l[1] < r[1]; });
        std::priority_queue<int> queue;
        int time = 0;
        for (std::vector<int> const &course : sortedCourses)
        {
            if ((time + course[0]) <= course[1])
            {
                queue.push(course[0]);
                time += course[0];
            }
            else if (!queue.empty() && (course[0] < queue.top()))
            {
                time += (course[0] - queue.top());
                queue.pop();
                queue.push(course[0]);
            }
        }
        return static_cast<int>(queue.size());
    }
};

}

namespace CourseScheduleIIITask
{

TEST(CourseScheduleIIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.scheduleCourse({{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}}));
    ASSERT_EQ(1, solution.scheduleCourse({{1, 2}}));
    ASSERT_EQ(0, solution.scheduleCourse({{3, 2}, {4, 3}}));
}

TEST(CourseScheduleIIITaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.scheduleCourse({{7, 17}, {3, 12}, {10, 20}, {9, 10}, {5, 20}, {10, 19}, {4, 18}}));
}

}