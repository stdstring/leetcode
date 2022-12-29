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
    [[nodiscard]] std::vector<int> getOrder(std::vector<std::vector<int>> const& tasks) const
    {
        std::vector<size_t> indices(tasks.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&tasks](size_t left, size_t right) { return tasks[left][0] < tasks[right][0]; });
        auto cmp = [](Task const& left, Task const& right) { return (left.second > right.second) || ((left.second == right.second) && (left.first > right.first)); };
        std::priority_queue<Task, std::vector<Task>, decltype(cmp)> queue(cmp);
        std::vector<int> result;
        size_t taskIndex = 0;
        long long currentTime = 0;
        while ((taskIndex < tasks.size()) || !queue.empty())
        {
            if (queue.empty() && (taskIndex < tasks.size()) && (tasks[indices[taskIndex]][0] > currentTime))
                currentTime = tasks[indices[taskIndex]][0];
            while ((taskIndex < tasks.size()) && (tasks[indices[taskIndex]][0] <= currentTime))
            {
                queue.emplace(indices[taskIndex], tasks[indices[taskIndex]][1]);
                ++taskIndex;
            }
            Task currentTask(queue.top());
            queue.pop();
            result.emplace_back(currentTask.first);
            currentTime += currentTask.second;
        }
        return result;
    }

private:
    typedef std::pair<size_t, int> Task;
};

}

namespace SingleThreadedCPUTask
{

TEST(SingleThreadedCPUTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 2, 3, 1}), solution.getOrder({{1, 2}, {2, 4}, {3, 2}, {4, 1}}));
    ASSERT_EQ(std::vector<int>({4, 3, 2, 0, 1}), solution.getOrder({{7, 10}, {7, 12}, {7, 5}, {7, 4}, {7, 2}}));
}

TEST(SingleThreadedCPUTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({6, 1, 2, 9, 4, 10, 0, 11, 5, 13, 3, 8, 12, 7}),
              solution.getOrder({{19, 13}, {16, 9}, {21, 10}, {32, 25}, {37, 4}, {49, 24}, {2, 15}, {38, 41}, {37, 34}, {33, 6}, {45, 4}, {18, 18}, {46, 39}, {12, 24}}));
    ASSERT_EQ(std::vector<int>({5, 0, 1, 3, 2, 4}), solution.getOrder({{5, 2}, {7, 2}, {9, 4}, {6, 3}, {5, 10}, {1, 1}}));
}

}