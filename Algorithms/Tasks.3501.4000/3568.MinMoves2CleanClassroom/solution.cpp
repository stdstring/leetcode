#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMoves(std::vector<std::string> const &classroom, int energy) const
    {
        const size_t rowCount = classroom.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = classroom.front().size();
        const size_t columnMax = columnCount - 1;
        std::unordered_map<size_t, int> litterMap;
        int litterMask = 1;
        int totalLitterMask = 0;
        size_t rowStart = 0;
        size_t columnStart = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (classroom[row][column] == 'S')
                {
                    rowStart = row;
                    columnStart = column;
                }
                if (classroom[row][column] == 'L')
                {
                    litterMap.emplace(row * columnCount + column, litterMask);
                    totalLitterMask |= litterMask;
                    litterMask <<= 1;
                }
            }
        }
        if (litterMap.empty())
            return 0;
        std::vector<std::vector<std::vector<int>>> steps(rowCount, std::vector<std::vector<int>>(columnCount, std::vector<int>(totalLitterMask + 1, -1)));
        steps[rowStart][columnStart][0] = energy;
        std::queue<MoveState> queue;
        queue.emplace(rowStart, columnStart, 0, energy, 0);
        while (!queue.empty())
        {
            MoveState current(queue.front());
            queue.pop();
            if (current.CollectedLitterMask == totalLitterMask)
                return static_cast<int>(current.StepCount);
            if (current.Energy == 0)
                continue;
            if (current.Row > 0)
                processNextStep(classroom, energy, litterMap, steps, queue, current, current.Row - 1, current.Column);
            if (current.Row < rowMax)
                processNextStep(classroom, energy, litterMap, steps, queue, current, current.Row + 1, current.Column);
            if (current.Column > 0)
                processNextStep(classroom, energy, litterMap, steps, queue, current, current.Row, current.Column - 1);
            if (current.Column < columnMax)
                processNextStep(classroom, energy, litterMap, steps, queue, current, current.Row, current.Column + 1);
        }
        return -1;
    }

private:
    struct MoveState
    {
        MoveState(size_t row, size_t column, size_t stepCount, int energy, int collectedLitterMask)
            : Row(row), Column(column), StepCount(stepCount), Energy(energy), CollectedLitterMask(collectedLitterMask)
        {
        }

        size_t Row;
        size_t Column;
        size_t StepCount;
        int Energy;
        int CollectedLitterMask;
    };

    void processNextStep(std::vector<std::string> const &classroom,
                         int initEnergy,
                         std::unordered_map<size_t, int> const &litterMap,
                         std::vector<std::vector<std::vector<int>>>&steps,
                         std::queue<MoveState> &queue,
                         MoveState const &currentState,
                         size_t nextRow,
                         size_t nextColumn) const
    {
        const size_t columnCount = classroom.front().size();
        if (classroom[nextRow][nextColumn] == 'X')
            return;
        int nextCollectedLitterMask = currentState.CollectedLitterMask;
        if (classroom[nextRow][nextColumn] == 'L')
            nextCollectedLitterMask |= litterMap.at(nextRow * columnCount + nextColumn);
        const int nextEnergy = classroom[nextRow][nextColumn] == 'R' ? initEnergy : currentState.Energy - 1;
        if (steps[nextRow][nextColumn][nextCollectedLitterMask] >= nextEnergy)
            return;
        steps[nextRow][nextColumn][nextCollectedLitterMask] = nextEnergy;
        queue.emplace(nextRow, nextColumn, currentState.StepCount + 1, nextEnergy, nextCollectedLitterMask);
    }
};

}

namespace MinMoves2CleanClassroomTask
{

TEST(MinMoves2CleanClassroomTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minMoves({"S.", "XL"}, 2));
    ASSERT_EQ(3, solution.minMoves({"LS", "RL"}, 4));
    ASSERT_EQ(-1, solution.minMoves({"L.S", "RXL"}, 3));
}

TEST(MinMoves2CleanClassroomTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minMoves({"S.", ".."}, 1));
}

}
