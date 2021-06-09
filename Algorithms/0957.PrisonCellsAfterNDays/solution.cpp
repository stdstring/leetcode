#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> prisonAfterNDays(std::vector<int> const &cells, int n) const
    {
        constexpr int cellsSize = 1 << CellsCount;
        std::vector<int> cellTransitions(cellsSize, -1);
        int stepCount = 0;
        std::vector<int> current(cells);
        int representation = cellsToInt(current);
        while (cellTransitions[representation] == -1 && stepCount < n)
        {
            current = nextDay(current);
            representation = cellTransitions[representation] = cellsToInt(current);
            ++stepCount;
        }
        if (stepCount == n)
            return current;
        const int cycleSize = findCycleSize(cellTransitions, representation);
        n = (n - (stepCount - cycleSize)) % cycleSize;
        for (int step = 0; step < n; ++step)
            representation = cellTransitions[representation];
        return intToCells(representation);
    }

private:
    static constexpr int CellsCount = 8;

    int cellsToInt(std::vector<int> const &cells) const
    {
        int result = 0;
        for (int cell : cells)
            result = (result << 1) + cell;
        return result;
    }

    std::vector<int> intToCells(int cellsRepresentation) const
    {
        std::vector<int> result;
        for (int cellPos = CellsCount - 1; cellPos >= 0; --cellPos)
            result.push_back((cellsRepresentation & (1 << cellPos)) > 0 ? 1 : 0);
        return result;
    }

    std::vector<int> nextDay(std::vector<int> const &cells) const
    {
        std::vector<int> nextCells(CellsCount, 0);
        for (size_t index = 0; index < CellsCount; ++index)
        {
            if (index == 0 || index == CellsCount - 1)
                nextCells[index] = 0;
            else
                nextCells[index] = cells[index - 1] == cells[index + 1] ? 1 : 0;
        }
        return nextCells;
    }

    int findCycleSize(std::vector<int> const &cellTransitions, int initial) const
    {
        int cycleSize = 1;
        int value = cellTransitions[initial];
        while (value != initial)
        {
            ++cycleSize;
            value = cellTransitions[value];
        }
        return cycleSize;
    }
};

}

namespace PrisonCellsAfterNDaysTask
{

TEST(PrisonCellsAfterNDaysTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 0, 1, 1, 0, 0, 0, 0}), solution.prisonAfterNDays({0, 1, 0, 1, 1, 0, 0, 1}, 7));
    ASSERT_EQ(std::vector<int>({0, 0, 1, 1, 1, 1, 1, 0}), solution.prisonAfterNDays({1, 0, 0, 1, 0, 0, 1, 0}, 1000000000));
}

}