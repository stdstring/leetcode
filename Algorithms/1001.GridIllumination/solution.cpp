#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> gridIllumination(int n, std::vector<std::vector<int>> const &lamps, std::vector<std::vector<int>> const &queries) const
    {
        const size_t rowMax = static_cast<size_t>(n) - 1;
        std::unordered_set<size_t> lampSet;
        std::unordered_multiset<size_t> illuminatedRows;
        std::unordered_multiset<size_t> illuminatedColumns;
        std::unordered_multiset<size_t> illuminatedMainDiagonals;
        std::unordered_multiset<size_t> illuminatedAuxDiagonals;
        for (std::vector<int> const &lamp : lamps)
        {
            size_t row = lamp[0];
            size_t column = lamp[1];
            initData(n, row, column, lampSet, illuminatedRows, illuminatedColumns, illuminatedMainDiagonals, illuminatedAuxDiagonals);
        }
        std::vector<int> answers;
        for (std::vector<int> const &query : queries)
        {
            size_t row = query[0];
            size_t column = query[1];
            answers.push_back(isIlluminated(n, row, column, illuminatedRows, illuminatedColumns, illuminatedMainDiagonals, illuminatedAuxDiagonals) ? 1 : 0);
            if (row > 0)
                strikeOutLampOnRow(n, row - 1, column, lampSet, illuminatedRows, illuminatedColumns, illuminatedMainDiagonals,  illuminatedAuxDiagonals);
            strikeOutLampOnRow(n, row, column, lampSet, illuminatedRows, illuminatedColumns, illuminatedMainDiagonals, illuminatedAuxDiagonals);
            if (row < rowMax)
                strikeOutLampOnRow(n, row + 1, column, lampSet, illuminatedRows, illuminatedColumns, illuminatedMainDiagonals, illuminatedAuxDiagonals);
        }
        return answers;
    }

private:
    void initData(size_t size,
                  size_t row,
                  size_t column,
                  std::unordered_set<size_t> &lampSet,
                  std::unordered_multiset<size_t> &illuminatedRows,
                  std::unordered_multiset<size_t> &illuminatedColumns,
                  std::unordered_multiset<size_t> &illuminatedMainDiagonals,
                  std::unordered_multiset<size_t> &illuminatedAuxDiagonals) const
    {
        if (lampSet.count(row * size + column) == 1)
            return;
        lampSet.insert(row * size + column);
        illuminatedRows.insert(row);
        illuminatedColumns.insert(column);
        illuminatedMainDiagonals.insert(row >= column ? size * (row - column) : column - row);
        const size_t inverseColumn = size - column - 1;
        illuminatedAuxDiagonals.insert(row >= inverseColumn ? size * (row - inverseColumn) : size - (inverseColumn - row) - 1);
    }

    bool isIlluminated(size_t size,
                       size_t row,
                       size_t column,
                       std::unordered_multiset<size_t> const &illuminatedRows,
                       std::unordered_multiset<size_t> const &illuminatedColumns,
                       std::unordered_multiset<size_t> const &illuminatedMainDiagonals,
                       std::unordered_multiset<size_t> const &illuminatedAuxDiagonals) const
    {
        if (illuminatedRows.count(row) > 0)
            return true;
        if (illuminatedColumns.count(column) > 0)
            return true;
        const size_t diagonalIndex = row >= column ? size * (row - column) : column - row;
        if (illuminatedMainDiagonals.count(diagonalIndex) > 0)
            return true;
        const size_t inverseColumn = size - column - 1;
        const size_t auxDiagonalIndex = row >= inverseColumn ? size * (row - inverseColumn) : size - (inverseColumn - row) - 1;
        if (illuminatedAuxDiagonals.count(auxDiagonalIndex) > 0)
            return true;
        return false;
    }

    void strikeOutLampOnRow(size_t size,
                            size_t row,
                            size_t column,
                            std::unordered_set<size_t> &lampSet,
                            std::unordered_multiset<size_t> &illuminatedRows,
                            std::unordered_multiset<size_t> &illuminatedColumns,
                            std::unordered_multiset<size_t> &illuminatedMainDiagonals,
                            std::unordered_multiset<size_t> &illuminatedAuxDiagonals) const
    {
        const size_t columnMax = static_cast<size_t>(size) - 1;
        if (column > 0)
            strikeOutLamp(size, row, column - 1, lampSet, illuminatedRows, illuminatedColumns, illuminatedMainDiagonals, illuminatedAuxDiagonals);
        strikeOutLamp(size, row, column, lampSet, illuminatedRows, illuminatedColumns, illuminatedMainDiagonals, illuminatedAuxDiagonals);
        if (column < columnMax)
            strikeOutLamp(size, row, column + 1, lampSet, illuminatedRows, illuminatedColumns, illuminatedMainDiagonals, illuminatedAuxDiagonals);
    }

    void strikeOutLamp(size_t size,
                       size_t row,
                       size_t column,
                       std::unordered_set<size_t> &lampSet,
                       std::unordered_multiset<size_t> &illuminatedRows,
                       std::unordered_multiset<size_t> &illuminatedColumns,
                       std::unordered_multiset<size_t> &illuminatedMainDiagonals,
                       std::unordered_multiset<size_t> &illuminatedAuxDiagonals) const
    {
        if (lampSet.count(row * size + column) == 0)
            return;
        lampSet.erase(row * size + column);
        illuminatedRows.erase(illuminatedRows.find(row));
        illuminatedColumns.erase(illuminatedColumns.find(column));
        const size_t diagonalIndex = row >= column ? size * (row - column) : column - row;
        illuminatedMainDiagonals.erase(illuminatedMainDiagonals.find(diagonalIndex));
        const size_t inverseColumn = size - column - 1;
        const size_t auxDiagonalIndex = row >= inverseColumn ? size * (row - inverseColumn) : size - (inverseColumn - row) - 1;
        illuminatedAuxDiagonals.erase(illuminatedAuxDiagonals.find(auxDiagonalIndex));
    }
};

}

namespace GridIlluminationTask
{

TEST(GridIlluminationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 0}), solution.gridIllumination(5, {{0, 0}, {4, 4}}, {{1, 1}, {1, 0}}));
    ASSERT_EQ(std::vector<int>({1, 1}), solution.gridIllumination(5, {{0, 0}, {4, 4}}, {{1, 1}, {1, 1}}));
    ASSERT_EQ(std::vector<int>({1, 1, 0}), solution.gridIllumination(5, {{0, 0}, {0, 4}}, {{0, 4}, {0, 1}, {1, 4}}));
}

TEST(GridIlluminationTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 1, 1}), solution.gridIllumination(5, {{0, 0}, {0, 1}, {0, 4}}, {{0, 0}, {0, 1}, {0, 2}}));
    ASSERT_EQ(std::vector<int>({1, 0, 1, 1, 0, 1}), solution.gridIllumination(6, {{2, 5}, {4, 2}, {0, 3}, {0, 5}, {1, 4}, {4, 2}, {3, 3}, {1, 0}}, {{4, 3}, {3, 1}, {5, 3}, {0, 5}, {4, 4}, {3, 3}}));
}

}
