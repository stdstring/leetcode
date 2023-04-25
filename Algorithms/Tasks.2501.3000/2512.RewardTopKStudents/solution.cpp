#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> topStudents(std::vector<std::string> const &positiveFeedback,
                                               std::vector<std::string> const &negativeFeedback,
                                               std::vector<std::string> const &report,
                                               std::vector<int> const &studentId,
                                               int k) const
    {
        const std::unordered_set<std::string> positiveFeedbackSet(positiveFeedback.cbegin(), positiveFeedback.cend());
        const std::unordered_set<std::string> negativeFeedbackSet(negativeFeedback.cbegin(), negativeFeedback.cend());
        auto cmp = [](StudentData const &l, StudentData const &r) { return (l.Result < r.Result) || ((l.Result == r.Result) && (l.Id > r.Id)); };
        std::priority_queue<StudentData, std::vector<StudentData>, decltype(cmp)> queue(cmp);
        for (size_t index = 0; index < report.size(); ++index)
        {
            int result = calcReportResult(report[index], positiveFeedbackSet, negativeFeedbackSet);
            queue.emplace(studentId[index], result);
        }
        std::vector<int> result;
        for (size_t index = 0; index < static_cast<size_t>(k); ++index)
        {
            result.emplace_back(queue.top().Id);
            queue.pop();
        }
        return result;
    }

private:
    struct StudentData
    {
        StudentData(int id, int result) : Id(id), Result(result)
        {
        }
        int Id;
        int Result;
    };

    [[nodiscard]] int calcReportResult(std::string const &report,
                                       std::unordered_set<std::string> const &positiveFeedbackSet,
                                       std::unordered_set<std::string> const &negativeFeedbackSet) const
    {
        int result = 0;
        for (size_t index = 0; index < report.size();)
        {
            size_t endIndex = report.find(' ', index);
            if (endIndex == std::string::npos)
                endIndex = report.size();
            std::string word(report.substr(index, endIndex - index));
            if (positiveFeedbackSet.count(word) != 0)
                result += 3;
            if (negativeFeedbackSet.count(word) != 0)
                result -= 1;
            index = endIndex + 1;
        }
        return result;
    }
};

}

namespace RewardTopKStudentsTask
{

TEST(RewardTopKStudentsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2}), solution.topStudents({"smart", "brilliant", "studious"}, {"not"}, {"this student is studious", "the student is smart"}, {1, 2}, 2));
    ASSERT_EQ(std::vector<int>({2, 1}), solution.topStudents({"smart", "brilliant", "studious"}, {"not"}, {"this student is not studious", "the student is smart"}, {1, 2}, 2));
}

}