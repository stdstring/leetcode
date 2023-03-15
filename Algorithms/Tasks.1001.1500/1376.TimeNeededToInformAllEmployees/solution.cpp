#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numOfMinutes(int n, int headID, std::vector<int> const &manager, std::vector<int> const &informTime) const
    {
        std::vector<std::vector<size_t>> children(n, std::vector<size_t>());
        for (size_t node = 0; node < children.size(); ++node)
        {
            if (manager[node] != -1)
                children[manager[node]].emplace_back(node);
        }
        return calcMinutesDuration(headID, children, informTime);
    }

private:
    [[nodiscard]] int calcMinutesDuration(size_t current, std::vector<std::vector<size_t>> const &children, std::vector<int> const &informTime) const
    {
        int childrenDuration = 0;
        for (const size_t child : children[current])
            childrenDuration = std::max(childrenDuration, calcMinutesDuration(child, children, informTime));
        return informTime[current] + childrenDuration;
    }
};

}

namespace TimeNeededToInformAllEmployeesTask
{

TEST(TimeNeededToInformAllEmployeesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.numOfMinutes(1, 0, {-1}, {0}));
    ASSERT_EQ(1, solution.numOfMinutes(6, 2, {2, 2, -1, 2, 2, 2}, {0, 0, 1, 0, 0, 0}));
}

}