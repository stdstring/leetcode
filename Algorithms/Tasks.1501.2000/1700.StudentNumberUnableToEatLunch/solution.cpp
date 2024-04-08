#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countStudents(std::vector<int> const &students, std::vector<int> const &sandwiches) const
    {
        size_t zeroCount = std::ranges::count(students, 0);
        size_t oneCount = students.size() - zeroCount;
        std::queue<int> studentsQueue;
        for (int studentPrefer : students)
            studentsQueue.emplace(studentPrefer);
        for (const int sandwich : sandwiches)
        {
            if (((sandwich == 0) && (zeroCount == 0)) || ((sandwich == 1) && (oneCount == 0)))
                break;
            while (studentsQueue.front() != sandwich)
            {
                studentsQueue.emplace(studentsQueue.front());
                studentsQueue.pop();
            }
            --(sandwich == 0 ? zeroCount : oneCount);
            studentsQueue.pop();
        }
        return static_cast<int>(studentsQueue.size());
    }
};

}

namespace StudentNumberUnableToEatLunchTask
{

TEST(StudentNumberUnableToEatLunchTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.countStudents({1, 1, 0, 0}, {0, 1, 0, 1}));
    ASSERT_EQ(3, solution.countStudents({1, 1, 1, 0, 0, 1}, {1, 0, 0, 0, 1, 1}));
}

}