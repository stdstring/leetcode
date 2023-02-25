#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canReach(std::vector<int> const &arr, int start) const
    {
        if (arr[start] == 0)
            return true;
        std::vector<bool> visited(arr.size(), false);
        std::queue<size_t> positions;
        processPosition(start, positions, visited);
        while (!positions.empty())
        {
            const size_t index = positions.front();
            const size_t number = arr[index];
            if (index >= number && !visited[index - number])
            {
                if (arr[index - number] == 0)
                    return true;
                processPosition(index - number, positions, visited);
            }
            if ((index + number < arr.size()) && !visited[index + number])
            {
                if (arr[index + number] == 0)
                    return true;
                processPosition(index + number, positions, visited);
            }
            positions.pop();
        }
        return false;
    }

private:
    void processPosition(size_t position, std::queue<size_t> &positions, std::vector<bool> &visited) const
    {
        positions.push(position);
        visited[position] = true;
    }
};

}

namespace JumpGameIIITask
{

TEST(JumpGameIIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canReach({4, 2, 3, 0, 3, 1, 2}, 5));
    ASSERT_EQ(true, solution.canReach({4, 2, 3, 0, 3, 1, 2}, 0));
    ASSERT_EQ(false, solution.canReach({3, 0, 2, 1, 2}, 2));
}

}