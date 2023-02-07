#include <algorithm>
#include <random>
#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    Solution(int m, int n) : _generator(std::random_device()()), _rowCount(m), _columnCount(n), _zeroCount(m * n), _ones(_rowCount, std::set<int>())
    {
    }

    std::vector<int> flip()
    {
        std::uniform_int_distribution<> distribution(0, _zeroCount - 1);
        const int randomNumber = distribution(_generator);
        std::vector<int> cell(findCell(randomNumber));
        _ones[cell[0]].insert(cell[1]);
        --_zeroCount;
        return cell;
    }

    void reset()
    {
        _zeroCount = _rowCount * _columnCount;
        _ones = std::vector<std::set<int>>(_rowCount, std::set<int>());
    }

private:
    std::mt19937 _generator;
    int _rowCount;
    int _columnCount;
    int _zeroCount;
    std::vector<std::set<int>> _ones;

    [[nodiscard]] std::vector<int> findCell(int randomNumber) const
    {
        int selectedRow = 0;
        int currentNumber = 0;
        while (currentNumber + static_cast<int>(_columnCount - _ones[selectedRow].size()) <= randomNumber)
        {
            currentNumber += static_cast<int>(_columnCount - _ones[selectedRow].size());
            ++selectedRow;
        }
        int selectedColumn = 0;
        for (auto iterator = _ones[selectedRow].cbegin(); iterator != _ones[selectedRow].cend(); ++iterator)
        {
            const int restNumber = randomNumber - currentNumber;
            if ((*iterator - selectedColumn) > restNumber)
                return {selectedRow, selectedColumn + restNumber};
            currentNumber += (*iterator - selectedColumn);
            selectedColumn = *iterator + 1;
        }
        return {selectedRow, selectedColumn + randomNumber - currentNumber};
    }
};

}

namespace
{

void checkFlipValue(std::vector<std::vector<int>> &expectedValues, Solution &solution)
{
    std::vector<int> actualValue(solution.flip());
    auto predicate = [&actualValue](std::vector<int> const& expectedValue) { return expectedValue[0] == actualValue[0] && expectedValue[1] == actualValue[1]; };
    const auto iterator = std::find_if(expectedValues.cbegin(), expectedValues.cend(), predicate);
    ASSERT_NE(expectedValues.cend(), iterator);
    expectedValues.erase(iterator);
}

}

namespace RandomFlipMatrixTask
{

TEST(RandomFlipMatrixTaskTests, Examples)
{
    Solution solution(3, 1);
    std::vector<std::vector<int>> expectedValues = {{0, 0}, {1, 0}, {2, 0}};
    checkFlipValue(expectedValues, solution);
    checkFlipValue(expectedValues, solution);
    checkFlipValue(expectedValues, solution);
    solution.reset();
    expectedValues = {{0, 0}, {1, 0}, {2, 0}};
    checkFlipValue(expectedValues, solution);
}

}