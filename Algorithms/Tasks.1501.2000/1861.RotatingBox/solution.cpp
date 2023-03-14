#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<char>> rotateTheBox(std::vector<std::vector<char>> const &box) const
    {
        constexpr char stone = '#';
        constexpr char obstacle = '*';
        constexpr char empty = '.';
        const size_t rowCount = box.size();
        const size_t columnCount = box.front().size();
        std::vector<std::vector<char>> result(columnCount, std::vector<char>(rowCount, empty));
        std::vector<size_t> height(rowCount, columnCount);
        for (size_t rrow = 0; rrow < rowCount; ++rrow)
        {
            const size_t row = rowCount - 1 - rrow;
            for (size_t rcolumn = 0; rcolumn < columnCount; ++rcolumn)
            {
                const size_t column = columnCount - 1 - rcolumn;
                switch (box[rrow][column])
                {
                case stone:
                    result[height[row] - 1][row] = stone;
                    --height[row];
                    break;
                case obstacle:
                    result[column][row] = obstacle;
                    height[row] = column;
                    break;
                default:
                    break;
                }
            }
        }
        return result;
    }
};

}

namespace RotatingBoxTask
{

TEST(RotatingBoxTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<char>>({{'.'}, {'#'}, {'#'}}), solution.rotateTheBox({{'#', '.', '#'}}));
    ASSERT_EQ(std::vector<std::vector<char>>({{'#', '.'}, {'#', '#'}, {'*', '*'}, {'.', '.'}}),
              solution.rotateTheBox({{'#', '.', '*', '.'}, {'#', '#', '*', '.'}}));
    ASSERT_EQ(std::vector<std::vector<char>>({{'.', '#', '#'}, {'.', '#', '#'}, {'#', '#', '*'}, {'#', '*', '.'}, {'#', '.', '*'}, {'#', '.', '.'}}),
              solution.rotateTheBox({{'#', '#', '*', '.', '*', '.'}, {'#', '#', '#', '*', '.', '.'}, {'#', '#', '#', '.', '#', '.'}}));
}

}