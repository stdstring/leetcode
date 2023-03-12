#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> sortTheStudents(std::vector<std::vector<int>> const &score, int k) const
    {
        const size_t studentsCount = score.size();
        const size_t examsCount = score.size();
        std::vector<size_t> studentIndices(studentsCount, 0);
        std::iota(studentIndices.begin(), studentIndices.end(), 0);
        auto comp = [&score, k](size_t left, size_t right){ return score[left][k] > score[right][k]; };
        std::sort(studentIndices.begin(), studentIndices.end(), comp);
        std::vector<std::vector<int>> result;
        for (const size_t studentIndex : studentIndices)
            result.emplace_back(score[studentIndex]);
        return result;
    }
};

}

namespace SortStudentsByTheirKthScoreTask
{

TEST(SortStudentsByTheirKthScoreTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{7, 5, 11, 2}, {10, 6, 9, 1}, {4, 8, 3, 15}}),
              solution.sortTheStudents({{10, 6, 9, 1}, {7, 5, 11, 2}, {4, 8, 3, 15}}, 2));
    ASSERT_EQ(std::vector<std::vector<int>>({{5, 6}, {3, 4}}), solution.sortTheStudents({{3, 4}, {5, 6}}, 0));
}

}