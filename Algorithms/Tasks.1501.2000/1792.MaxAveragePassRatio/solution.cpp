#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double maxAverageRatio(std::vector<std::vector<int>> const &classes, int extraStudents) const
    {
        if (classes.size() == 1)
            return 1.0 * (classes[0][0] + extraStudents) / (classes[0][1] + extraStudents);
        typedef std::pair<int, int> TClass;
        auto cmp = [](TClass const& l, TClass const& r)
        {
            // max((a+1)/(b+1) - a/b) => we calculate (a + 1) * b - a * (b + 1) = a * b + b - (a * b + a) = b - a
            double lDiff = 1.0 * (l.second - l.first) / (1.0 * l.second * (l.second + 1));
            double rDiff = 1.0 * (r.second - r.first) / (1.0 * r.second * (r.second + 1));
            return lDiff < rDiff;
        };
        std::priority_queue<TClass, std::vector<TClass>, decltype(cmp)> classQueue(cmp);
        double ratioSum = 0;
        for (std::vector<int> const &entry : classes)
        {
            ratioSum += (1.0 * entry[0] / entry[1]);
            if (entry[0] < entry[1])
                classQueue.emplace(entry[0], entry[1]);
        }
        if (classQueue.empty())
            return 1.0;
        for (int extraStudent = 0; extraStudent < extraStudents; ++extraStudent)
        {
            auto[currentFirst, currentSecond] = classQueue.top();
            classQueue.pop();
            ratioSum -= (1.0 * currentFirst / currentSecond);
            ++currentFirst;
            ++currentSecond;
            classQueue.emplace(currentFirst, currentSecond);
            ratioSum += (1.0 * currentFirst / currentSecond);
        }
        return ratioSum / static_cast<int>(classes.size());
    }
};

}

namespace MaxAveragePassRatioTask
{

TEST(MaxAveragePassRatioTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_NEAR(0.78333, solution.maxAverageRatio({{1, 2}, {3, 5}, {2, 2}}, 2), 0.00001);
    ASSERT_NEAR(0.53485, solution.maxAverageRatio({{2, 4}, {3, 9}, {4, 5}, {2, 10}}, 4), 0.00001);
}

TEST(MaxAveragePassRatioTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_NEAR(1.00000, solution.maxAverageRatio({{2, 2}, {3, 3}, {4, 4}}, 2), 0.00001);
}

}