#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> assignTasks(std::vector<int> const &servers, std::vector<int> const &tasks) const
    {
        using TUsageData = std::pair<long long, size_t>;
        auto usageComp = [](TUsageData const &l, TUsageData const &r) { return l.first > r.first; };
        auto serverComp = [&servers](size_t l, size_t r)
        {
            if (servers[l] != servers[r])
                return servers[l] > servers[r];
            return l > r;
        };
        std::priority_queue<TUsageData, std::vector<TUsageData>, decltype(usageComp)> usageQueue(usageComp);
        std::priority_queue<size_t, std::vector<size_t>, decltype(serverComp)> freeQueue(serverComp);
        for (size_t index = 0; index < servers.size(); ++index)
            freeQueue.emplace(index);
        std::vector<int> result(tasks.size(), 0);
        long long currentTime = 0;
        for (size_t index = 0; index < tasks.size(); ++index)
        {
            currentTime = std::max(currentTime, static_cast<long long>(index));
            if (freeQueue.empty() && (currentTime < usageQueue.top().first))
                currentTime = usageQueue.top().first;
            while (!usageQueue.empty() && (usageQueue.top().first <= currentTime))
            {
                freeQueue.emplace(usageQueue.top().second);
                usageQueue.pop();
            }
            result[index] = static_cast<int>(freeQueue.top());
            usageQueue.emplace(currentTime + tasks[index], freeQueue.top());
            freeQueue.pop();
        }
        return result;
    }
};

}

namespace ProcessTasksUsingServersTask
{

TEST(ProcessTasksUsingServersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 2, 0, 2, 1, 2}), solution.assignTasks({3, 3, 2}, {1, 2, 3, 2, 1, 2}));
    ASSERT_EQ(std::vector<int>({1, 4, 1, 4, 1, 3, 2}), solution.assignTasks({5, 1, 4, 3, 2}, {2, 1, 2, 4, 5, 2, 1}));
}

}
