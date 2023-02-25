#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int leastInterval(std::vector<char> const &tasks, int n) const
    {
        std::unordered_map<char, size_t> taskMap;
        for (char task : tasks)
            ++taskMap[task];
        auto cmp = [](Task const &left, Task const &right) { return left.Count < right.Count; };
        std::priority_queue<Task, std::vector<Task>, decltype(cmp)> activeTasksQueue(cmp);
        std::queue<Task> delayedTasksQueue;
        for (auto const &[type, count] : taskMap)
            activeTasksQueue.emplace(type, count);
        int currentTime = 0;
        while (!activeTasksQueue.empty() || !delayedTasksQueue.empty())
        {
            if (!delayedTasksQueue.empty() && (delayedTasksQueue.front().LastExecuted + n < currentTime))
            {
                activeTasksQueue.push(delayedTasksQueue.front());
                delayedTasksQueue.pop();
            }
            if (activeTasksQueue.empty())
            {
                currentTime += (delayedTasksQueue.front().LastExecuted + n - currentTime + 1);
                activeTasksQueue.push(delayedTasksQueue.front());
                delayedTasksQueue.pop();
            }
            Task currentTask(activeTasksQueue.top());
            activeTasksQueue.pop();
            if (currentTask.Count > 1)
            {
                --currentTask.Count;
                currentTask.LastExecuted = currentTime;
                delayedTasksQueue.push(currentTask);
            }
            ++currentTime;
        }
        return currentTime;
    }

private:
    struct Task
    {
        Task(char type, size_t count) : Type(type), Count(count)
        {
        }

        char Type;
        size_t Count;
        int LastExecuted = -1;
    };
};

}

namespace TaskSchedulerTask
{

TEST(TaskSchedulerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.leastInterval({'A', 'A', 'A', 'B', 'B', 'B'}, 2));
    ASSERT_EQ(6, solution.leastInterval({'A', 'A', 'A', 'B', 'B', 'B'}, 0));
    ASSERT_EQ(16, solution.leastInterval({'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'}, 2));
}

}