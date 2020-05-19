const char Empty = '.';

class Solution
{
public:
    bool isValidSudoku(std::vector<std::vector<char>> const &board)
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
    bool checkHorizontalLine(std::vector<std::vector<char>> const &board, int x)
    {
        int checkMask = 0;
        for(int y = 0; y < 9; ++y)
        {
            if (board[x][y] != Empty)
            {
                int value = board[x][y] - '0';
                int valueMask = 1 << value;
                if ((checkMask & valueMask) > 0)
                    return false;
                checkMask |= valueMask;
            }
        }
        return true;
    }

    bool checkVerticalLine(std::vector<std::vector<char>> const &board, int y)
    {
        int checkMask = 0;
        for(int x = 0; x < 9; ++x)
        {
            if (board[x][y] != Empty)
            {
                int value = board[x][y] - '0';
                int valueMask = 1 << value;
                if ((checkMask & valueMask) > 0)
                    return false;
                checkMask |= valueMask;
            }
        }
        return true;
    }

    bool checkSquare(std::vector<std::vector<char>> const &board, int leftX, int topY)
    {
        int checkMask = 0;
        for(int x = 0; x < 3; ++x)
        {
            for(int y = 0; y < 3; ++y)
            {
                if (board[leftX + x][topY + y] != Empty)
                {
                    int value = board[leftX + x][topY + y] - '0';
                    int valueMask = 1 << value;
                    if ((checkMask & valueMask) > 0)
                        return false;
                    checkMask |= valueMask;
                }
            }
        }
        return true;
    }
};