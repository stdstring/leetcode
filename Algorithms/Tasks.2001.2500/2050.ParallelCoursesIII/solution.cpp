#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumTime(int n, std::vector<std::vector<int>> const &relations, std::vector<int> const &time) const
    {
        std::vector<bool> isDestNodes(n, true);
        std::vector<std::vector<size_t>> prerequisites(n, std::vector<size_t>());
        for (std::vector<int> const &relation : relations)
        {
            const int prevCourse = relation[0] - 1;
            const int nextCourse = relation[1] - 1;
            prerequisites[nextCourse].emplace_back(prevCourse);
            isDestNodes[prevCourse] = false;
        }
        std::vector<int> answers(n, 0);
        int usedTime = 0;
        for (size_t index = 0; index < isDestNodes.size(); ++index)
        {
            if (isDestNodes[index])
                usedTime = std::max(usedTime, calcMaxUsedTime(index, prerequisites, time, answers));
        }
        return usedTime;
    }

private:
    [[nodiscard]] int calcMaxUsedTime(size_t current, std::vector<std::vector<size_t>> const &prerequisites, std::vector<int> const &time, std::vector<int> &answers) const
    {
        if (answers[current] != 0)
            return answers[current];
        int maxPrerequisitesCost = 0;
        for (const size_t prerequisite : prerequisites[current])
            maxPrerequisitesCost = std::max(maxPrerequisitesCost, calcMaxUsedTime(prerequisite, prerequisites, time, answers));
        answers[current] = time[current] + maxPrerequisitesCost;
        return answers[current];
    }
};

}

namespace ParallelCoursesIIITask
{

TEST(ParallelCoursesIIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.minimumTime(3, {{1, 3}, {2, 3}}, {3, 2, 5}));
    ASSERT_EQ(12, solution.minimumTime(5, {{1, 5}, {2, 5}, {3, 5}, {3, 4}, {4, 5}}, {1, 2, 3, 4, 5}));
}

}