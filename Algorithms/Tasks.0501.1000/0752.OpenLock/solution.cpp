#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int openLock(std::vector<std::string> const &deadends, std::string const &target) const
    {
        std::unordered_set<int> deadendNumbers;
        for (std::string const &deadend : deadends)
            deadendNumbers.insert(std::stoi(deadend));
        if (deadendNumbers.count(0) == 1)
            return -1;
        const int targetNumber = std::stoi(target);
        constexpr size_t caseCount = 10000;
        std::vector<size_t> distances(caseCount, INT_MAX);
        distances[0] = 0;
        std::queue<int> queue;
        queue.push(0);
        while (!queue.empty())
        {
            if (queue.front() == targetNumber)
                return static_cast<int>(distances[targetNumber]);
            for (int nextNumber : generateNextNumbers(queue.front()))
            {
                if (deadendNumbers.count(nextNumber) == 0 && distances[nextNumber] == INT_MAX)
                {
                    distances[nextNumber] = distances[queue.front()] + 1;
                    queue.push(nextNumber);
                }
            }
            queue.pop();
        }
        return -1;
    }

private:
    std::vector<int> generateNextNumbers(int current) const
    {
        const int digit4 = current % 10;
        const int digit3 = (current / 10) % 10;
        const int digit2 = (current / 100) % 10;
        const int digit1 = current / 1000;
        const int nextNumber4Up = digit1 * 1000 + digit2 * 100 + digit3 * 10 + (digit4 == 9 ? 0 : digit4 + 1);
        const int nextNumber4Down = digit1 * 1000 + digit2 * 100 + digit3 * 10 + (digit4 == 0 ? 9 : digit4 - 1);
        const int nextNumber3Up = digit1 * 1000 + digit2 * 100 + (digit3 == 9 ? 0 : digit3 + 1) * 10 + digit4;
        const int nextNumber3Down = digit1 * 1000 + digit2 * 100 + (digit3 == 0 ? 9 : digit3 - 1) * 10 + digit4;
        const int nextNumber2Up = digit1 * 1000 + (digit2 == 9 ? 0 : digit2 + 1) * 100 + digit3 * 10 + digit4;
        const int nextNumber2Down = digit1 * 1000 + (digit2 == 0 ? 9 : digit2 - 1) * 100 + digit3 * 10 + digit4;
        const int nextNumber1Up = (digit1 == 9 ? 0 : digit1 + 1) * 1000 + digit2 * 100 + digit3 * 10 + digit4;
        const int nextNumber1Down = (digit1 == 0 ? 9 : digit1 - 1) * 1000 + digit2 * 100 + digit3 * 10 + digit4;
        return {nextNumber4Up, nextNumber4Down, nextNumber3Up, nextNumber3Down, nextNumber2Up, nextNumber2Down, nextNumber1Up, nextNumber1Down};
    }
};

}

namespace OpenLockTask
{

TEST(OpenLockTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.openLock({"0201", "0101", "0102", "1212", "2002"}, "0202"));
    ASSERT_EQ(1, solution.openLock({"8888"}, "0009"));
    ASSERT_EQ(-1, solution.openLock({"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"}, "8888"));
    ASSERT_EQ(-1, solution.openLock({"0000"}, "8888"));
}

TEST(OpenLockTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(3, solution.openLock({"2110", "0202", "1222", "2221", "1010"}, "2010"));
}

}