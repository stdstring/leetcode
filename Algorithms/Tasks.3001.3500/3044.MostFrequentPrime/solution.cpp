#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int mostFrequentPrime(std::vector<std::vector<int>> const &mat) const
    {
        const int rowCount = static_cast<int>(mat.size());
        const int columnCount = static_cast<int>(mat.front().size());
        std::unordered_map<int, size_t> numbers;
        for (int row  = 0; row < rowCount; ++row)
        {
            for (int column = 0; column < columnCount; ++column)
            {
                generateNumbersFromCell(mat, row, column, 1, 0, numbers);
                generateNumbersFromCell(mat, row, column, -1, 0, numbers);
                generateNumbersFromCell(mat, row, column, 0, 1, numbers);
                generateNumbersFromCell(mat, row, column, 0, -1, numbers);
                generateNumbersFromCell(mat, row, column, 1, 1, numbers);
                generateNumbersFromCell(mat, row, column, -1, 1, numbers);
                generateNumbersFromCell(mat, row, column, 1, -1, numbers);
                generateNumbersFromCell(mat, row, column, -1, -1, numbers);
            }
        }
        int bestPrime = -1;
        size_t bestPrimeCount = 0;
        for (auto const [number, count] : numbers)
        {
            if (!isPrime(number))
                continue;
            if (bestPrimeCount == count)
                bestPrime = std::max(bestPrime, number);
            if (bestPrimeCount < count)
            {
                bestPrimeCount = count;
                bestPrime = number;
            }
        }
        return bestPrime;
    }

private:
    void generateNumbersFromCell(std::vector<std::vector<int>> const &mat,
                                 int row,
                                 int column,
                                 int rowDelta,
                                 int columnDelta,
                                 std::unordered_map<int, size_t> &numbers) const
    {
        const int rowCount = static_cast<int>(mat.size());
        const int columnCount = static_cast<int>(mat.front().size());
        int number = 0;
        for (;(row >= 0) && (row < rowCount) && (column >= 0) && (column < columnCount); row += rowDelta, column += columnDelta)
        {
            number = 10 * number + mat[row][column];
            if (number > 9)
                ++numbers[number];
        }
    }

    [[nodiscard]] bool isPrime(int number) const
    {
        if ((number % 2) == 0)
            return false;
        for (int factor = 3; factor * factor <= number; factor += 2)
        {
            if ((number % factor) == 0)
                return false;
        }
        return true;
    }
};

}

namespace MostFrequentPrimeTask
{

TEST(MostFrequentPrimeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(19, solution.mostFrequentPrime({{1, 1}, {9, 9}, {1, 1}}));
    ASSERT_EQ(-1, solution.mostFrequentPrime({{7}}));
    ASSERT_EQ(97, solution.mostFrequentPrime({{9, 7, 8}, {4, 6, 5}, {2, 8, 6}}));
}

}