#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxProfitAssignment(std::vector<int> const &difficulty, std::vector<int> const &profit, std::vector<int> const &worker) const
    {
        std::vector<size_t> jobs(difficulty.size(), 0);
        std::iota(jobs.begin(), jobs.end(), 0);
        std::sort(jobs.begin(), jobs.end(), [&profit](size_t left, size_t right){ return profit[left] > profit[right]; });
        std::vector<int> sortedWorkers(worker);
        std::sort(sortedWorkers.begin(), sortedWorkers.end(), std::greater<int>());
        int result = 0;
        for (size_t workerIndex = 0, jobIndex = 0; (workerIndex < sortedWorkers.size()) && (jobIndex < jobs.size());)
        {
            if (sortedWorkers[workerIndex] >= difficulty[jobs[jobIndex]])
            {
                result += profit[jobs[jobIndex]];
                ++workerIndex;
            }
            else
                ++jobIndex;
        }
        return result;
    }
};

}

namespace MostProfitAssigningWorkTask
{

TEST(MostProfitAssigningWorkTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(100, solution.maxProfitAssignment({2, 4, 6, 8, 10}, {10, 20, 30, 40, 50}, {4, 5, 6, 7}));
    ASSERT_EQ(0, solution.maxProfitAssignment({85, 47, 57}, {24, 66, 99}, {40, 25, 25}));
}

}