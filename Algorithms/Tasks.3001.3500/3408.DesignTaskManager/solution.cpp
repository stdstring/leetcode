#include <set>
#include <vector>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class TaskManager
{
public:
    TaskManager(std::vector<std::vector<int>> const &tasks)
    {
        for (std::vector<int> const &task : tasks)
            add(task[0], task[1], task[2]);
    }

    void add(int userId, int taskId, int priority)
    {
        Task task(userId, taskId, priority);
        _taskMap.emplace(taskId, task);
        _taskQueue.insert(task);
    }

    void edit(int taskId, int newPriority)
    {
        Task &task = _taskMap.at(taskId);
        _taskQueue.erase(task);
        task.priority = newPriority;
        _taskQueue.insert(task);
    }

    void rmv(int taskId)
    {
        auto iterator = _taskMap.find(taskId);
        _taskQueue.erase(iterator->second);
        _taskMap.erase(iterator);
    }

    int execTop()
    {
        if (_taskQueue.empty())
            return -1;
        int taskId = _taskQueue.cbegin()->taskId;
        int userId = _taskQueue.cbegin()->userId;
        _taskQueue.erase(_taskQueue.cbegin());
        _taskMap.erase(taskId);
        return userId;
    }

private:
    struct Task
    {
        Task(int userId, int taskId, int priority) : userId(userId), taskId(taskId), priority(priority)
        {
        }
        int userId = -1;
        int taskId = -1;
        int priority = -1;
    };

    struct TaskComp
    {
        bool operator()(Task const &left, Task const &right) const
        {
            return (left.priority > right.priority) || ((left.priority == right.priority) && (left.taskId > right.taskId));
        }
    };

    std::unordered_map<int, Task> _taskMap;
    std::set<Task, TaskComp> _taskQueue;
};

}

namespace DesignTaskManagerTask
{

TEST(DesignTaskManagerTaskTests, Examples)
{
    TaskManager taskManager({{1, 101, 10}, {2, 102, 20}, {3, 103, 15}});
    ASSERT_NO_THROW(taskManager.add(4, 104, 5));
    ASSERT_NO_THROW(taskManager.edit(102, 8));
    ASSERT_EQ(3, taskManager.execTop());
    ASSERT_NO_THROW(taskManager.rmv(101));
    ASSERT_NO_THROW(taskManager.add(5, 105, 15));
    ASSERT_EQ(5, taskManager.execTop());
}

}