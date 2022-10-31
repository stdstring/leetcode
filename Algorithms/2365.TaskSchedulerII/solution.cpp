#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{
class Solution
{
public:
    [[nodiscard]] long long taskSchedulerII(std::vector<int> const &tasks, int space) const
    {
        std::unordered_map<int, long long> taskMap;
        long long daysCount = 0;
        for (int task : tasks)
        {
            auto iterator = taskMap.find(task);
            if (iterator == taskMap.end())
                taskMap.emplace(task, daysCount);
            else
            {
                if ((iterator->second + space + 1) > daysCount)
                    daysCount += (iterator->second + space + 1 - daysCount);
                iterator->second = daysCount;
            }
            ++daysCount;
        }
        return daysCount;
    }
};

}

namespace TaskSchedulerIITask
{

TEST(TaskSchedulerIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.taskSchedulerII({1, 2, 1, 2, 3, 1}, 3));
    ASSERT_EQ(6, solution.taskSchedulerII({5, 8, 8, 5}, 2));
}

}