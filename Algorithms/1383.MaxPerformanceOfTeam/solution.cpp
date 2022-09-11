#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxPerformance(int n, std::vector<int> const &speed, std::vector<int> const &efficiency, int k) const
    {
        constexpr int64_t modValue = 1000000007;
        std::vector<size_t> indices(efficiency.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&efficiency](size_t const &l, size_t const &r){ return efficiency[l] > efficiency[r]; });
        int64_t performance = 0;
        int64_t sum = 0;
        std::priority_queue<int, std::vector<int>, std::greater<int>> speedQueue;
        for (size_t index = 0; index < k; ++index)
        {
            sum += speed[indices[index]];
            speedQueue.push(speed[indices[index]]);
            performance = std::max(performance, sum * efficiency[indices[index]]);
        }
        for (size_t index = k; index < indices.size(); ++index)
        {
            sum -= speedQueue.top();
            speedQueue.pop();
            sum += speed[indices[index]];
            speedQueue.push(speed[indices[index]]);
            performance = std::max(performance, sum * efficiency[indices[index]]);
        }
        return static_cast<int>(performance % modValue);
    }
};

}

namespace MaxPerformanceOfTeamTask
{

TEST(MaxPerformanceOfTeamTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(60, solution.maxPerformance(6, {2, 10, 3, 1, 5, 8}, {5, 4, 3, 9, 7, 2}, 2));
    ASSERT_EQ(68, solution.maxPerformance(6, {2, 10, 3, 1, 5, 8}, {5, 4, 3, 9, 7, 2}, 3));
    ASSERT_EQ(72, solution.maxPerformance(6, {2, 10, 3, 1, 5, 8}, {5, 4, 3, 9, 7, 2}, 4));
}

TEST(MaxPerformanceOfTeamTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(56, solution.maxPerformance(3, {2, 8, 2}, {2, 7, 1}, 2));
}

}