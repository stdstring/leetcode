#include <vector>

#include "gtest/gtest.h"

namespace
{

const char Empty = '.';

class Solution
{
public:
    bool isValidSudoku(std::vector<std::vector<char>> const &board) const
    {
        for(int x = 0; x < 9; ++x)
        {
            if (!checkHorizontalLine(board, x))
                return false;
        }
        for(int y = 0; y < 9; ++y)
        {
            if (!checkVerticalLine(board, y))
                return false;
        }
        for(int x = 0; x < 3; ++x)
        {
            for(int y = 0; y < 3; ++y)
            {
                if(!checkSquare(board, x * 3, y * 3))
                    return false;
            }
        }
        return true;
    }

private:
    bool checkHorizontalLine(std::vector<std::vector<char>> const &board, int x) const
    {
        int checkMask = 0;
        for(int y = 0; y < 9; ++y)
        {
            if (board[x][y] != Empty)
            {
                const int value = board[x][y] - '0';
                const int valueMask = 1 << value;
                if ((checkMask & valueMask) > 0)
                    return false;
                checkMask |= valueMask;
            }
        }
        return true;
    }

    bool checkVerticalLine(std::vector<std::vector<char>> const &board, int y) const
    {
        int checkMask = 0;
        for(int x = 0; x < 9; ++x)
        {
            if (board[x][y] != Empty)
            {
                const int value = board[x][y] - '0';
                const int valueMask = 1 << value;
                if ((checkMask & valueMask) > 0)
                    return false;
                checkMask |= valueMask;
            }
        }
        return true;
    }

    bool checkSquare(std::vector<std::vector<char>> const &board, int leftX, int topY) const
    {
        int checkMask = 0;
        for(int x = 0; x < 3; ++x)
        {
            for(int y = 0; y < 3; ++y)
            {
                if (board[leftX + x][topY + y] != Empty)
                {
                    const int value = board[leftX + x][topY + y] - '0';
                    const int valueMask = 1 << value;
                    if ((checkMask & valueMask) > 0)
                        return false;
                    checkMask |= valueMask;
                }
            }
        }
        return true;
    }
};

}

namespace ValidSudokuTask
{

TEST(ValidSudokuTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isValidSudoku({{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}}));
    ASSERT_EQ(false, solution.isValidSudoku({{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                                             {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                             {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                             {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                             {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                             {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                             {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                             {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                             {'.', '.', '.', '.', '8', '.', '.', '7', '9'}}));
}

}