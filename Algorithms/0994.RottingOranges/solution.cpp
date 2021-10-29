#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct OrangeData
{
    OrangeData(size_t row, size_t column, size_t rottingTime) : Row(row), Column(column), RottingTime(rottingTime)
    {
    }

    size_t Row;
    size_t Column;
    size_t RottingTime;
};

class Solution
{
public:
    [[nodiscard]] int orangesRotting(std::vector<std::vector<int>> const &grid) const
    {
        std::vector<std::vector<int>> gridData(grid);
        size_t totalRottingTime = 0;
        size_t freshCount = 0;
        std::queue<OrangeData> rottingOranges;
        for (size_t row = 0; row < gridData.size(); ++row)
        {
            for (size_t column = 0; column < gridData[row].size(); ++column)
            {
                if (gridData[row][column] == FreshOrange)
                    ++freshCount;
                if (gridData[row][column] == RottingOrange)
                    rottingOranges.emplace(row, column, 0);
            }
        }
        while (!rottingOranges.empty())
        {
            const size_t row = rottingOranges.front().Row;
            const size_t column = rottingOranges.front().Column;
            const size_t rottingTime = rottingOranges.front().RottingTime;
            totalRottingTime = std::max(totalRottingTime, rottingTime);
            if (row > 0 && gridData[row - 1][column] == FreshOrange)
                updateOrange(gridData, row - 1, column, rottingTime + 1, rottingOranges, freshCount);
            if (row < (grid.size() - 1) && gridData[row + 1][column] == FreshOrange)
                updateOrange(gridData, row + 1, column, rottingTime + 1, rottingOranges, freshCount);
            if (column > 0 && gridData[row][column - 1] == FreshOrange)
                updateOrange(gridData, row, column - 1, rottingTime + 1, rottingOranges, freshCount);
            if (column < (gridData[row].size() - 1) && gridData[row][column + 1] == FreshOrange)
                updateOrange(gridData, row, column + 1, rottingTime + 1, rottingOranges, freshCount);
            rottingOranges.pop();
        }
        return freshCount == 0 ? static_cast<int>(totalRottingTime) : -1;
    }

private:
    static constexpr int FreshOrange = 1;
    static constexpr int RottingOrange = 2;

    void updateOrange(std::vector<std::vector<int>> &gridData, size_t row, size_t column, size_t rottingTime, std::queue<OrangeData> &rottingOranges, size_t &freshCount) const
    {
        gridData[row][column] = RottingOrange;
        rottingOranges.emplace(row, column, rottingTime);
        --freshCount;
    }
};

}

namespace RottingOrangesTask
{

TEST(RottingOrangesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.orangesRotting({{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}));
    ASSERT_EQ(-1, solution.orangesRotting({{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}));
    ASSERT_EQ(0, solution.orangesRotting({{0, 2}}));
}

}