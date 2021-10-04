#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string alphabetBoardPath(std::string const &target) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<std::string> board({"abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"});
        std::array<std::pair<size_t, size_t>, alphabetSize> coords;
        for (size_t row = 0; row < board.size(); ++row)
        {
            for (size_t column = 0; column < board[row].size(); ++column)
                coords[board[row][column] - alphabetStart] = {row, column};
        }
        std::string dest;
        size_t currentRow = 0;
        size_t currentColumn = 0;
        for (char letter : target)
        {
            const size_t letterRow = coords[letter - alphabetStart].first;
            const size_t letterColumn = coords[letter - alphabetStart].second;
            if (letter == 'z')
            {
                moveHorizontal(currentColumn, letterColumn, dest);
                moveVertical(currentRow, letterRow, dest);
            }
            else
            {
                moveVertical(currentRow, letterRow, dest);
                moveHorizontal(currentColumn, letterColumn, dest);
            }
            currentRow = letterRow;
            currentColumn = letterColumn;
            dest.push_back('!');
        }
        return dest;
    }

private:
    void moveHorizontal(size_t currentColumn, size_t letterColumn, std::string &dest) const
    {
        while (currentColumn != letterColumn)
        {
            if (currentColumn > letterColumn)
            {
                dest.push_back('L');
                --currentColumn;
            }
            else
            {
                dest.push_back('R');
                ++currentColumn;
            }
        }
    }

    void moveVertical(size_t currentRow, size_t letterRow, std::string &dest) const
    {
        while (currentRow != letterRow)
        {
            if (currentRow > letterRow)
            {
                dest.push_back('U');
                --currentRow;
            }
            else
            {
                dest.push_back('D');
                ++currentRow;
            }
        }
    }
};

}

namespace AlphabetBoardPathTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("DDR!UURRR!!DDD!", solution.alphabetBoardPath("leet"));
    ASSERT_EQ("RR!DDRR!UUL!R!", solution.alphabetBoardPath("code"));
}

}