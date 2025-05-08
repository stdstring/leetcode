#include <functional>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minTimeToReach(std::vector<std::vector<int>> const &moveTime) const
    {
        const size_t rowCount = moveTime.size();
        const size_t columnCount = moveTime.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<int>> timeData(rowCount, std::vector<int>(columnCount, INT_MAX));
        timeData[0][0] = 0;
        std::vector<std::vector<bool>> processed(rowCount, std::vector<bool>(columnCount, false));
        const Comparer comparer = [](CellData const &l, CellData const &r) { return l.Time > r.Time; };
        std::priority_queue<CellData, std::vector<CellData>, Comparer> cellQueue(comparer);
        cellQueue.emplace(0, 0, 0);
        while (!cellQueue.empty())
        {
            const CellData current(cellQueue.top());
            cellQueue.pop();
            if (processed[current.Row][current.Column])
                continue;
            processed[current.Row][current.Column] = true;
            if ((current.Row == rowMax) && (current.Column == columnMax))
                break;
            if ((current.Row > 0) && !processed[current.Row - 1][current.Column])
                processNextStep(current.Row - 1, current.Column, current.Time, moveTime, cellQueue, timeData);
            if ((current.Row < rowMax) && !processed[current.Row + 1][current.Column])
                processNextStep(current.Row + 1, current.Column, current.Time, moveTime, cellQueue, timeData);
            if ((current.Column > 0) && !processed[current.Row][current.Column - 1])
                processNextStep(current.Row, current.Column - 1, current.Time, moveTime, cellQueue, timeData);
            if ((current.Column < columnMax) && !processed[current.Row][current.Column + 1])
                processNextStep(current.Row, current.Column + 1, current.Time, moveTime, cellQueue, timeData);
        }
        return timeData[rowMax][columnMax];
    }

private:
    struct CellData
    {
        CellData(size_t row, size_t column, int time) : Row(row), Column(column), Time(time)
        {
        }

        size_t Row;
        size_t Column;
        int Time;
    };

    typedef std::function<bool(CellData const&, CellData const&)> Comparer;

    void processNextStep(size_t row,
                         size_t column,
                         int time,
                         std::vector<std::vector<int>> const &moveTime,
                         std::priority_queue<CellData, std::vector<CellData>, Comparer> &cellQueue,
                         std::vector<std::vector<int>> &timeData) const
    {
        int nextTime = std::max(time, moveTime[row][column]) + 1;
        if (nextTime >= timeData[row][column])
            return;
        timeData[row][column] = nextTime;
        cellQueue.emplace(row, column, nextTime);
    }
};

}

namespace FindMinTimeToReachLastRoom1Task
{

TEST(FindMinTimeToReachLastRoom1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minTimeToReach({{0, 4}, {4, 4}}));
    ASSERT_EQ(3, solution.minTimeToReach({{0, 0, 0}, {0, 0, 0}}));
    ASSERT_EQ(3, solution.minTimeToReach({{0, 1}, {1, 2}}));
}

TEST(FindMinTimeToReachLastRoom1TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minTimeToReach({{0, 0, 0, 0}, {0, 0, 0, 0}}));
}

}