#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) const
    {
        std::vector<std::vector<int>> coords;
        for (int row = 0; row < rows; ++row)
        {
            for (int column = 0; column < cols; ++column)
                coords.push_back({row, column});
        }
        auto comparer = [rCenter, cCenter](std::vector<int> const &l, std::vector<int> const &r)
        {
            return (std::abs(l[0] - rCenter) + std::abs(l[1] - cCenter)) < (std::abs(r[0] - rCenter) + std::abs(r[1] - cCenter));
        };
        std::sort(coords.begin(), coords.end(), comparer);
        return coords;
    }
};

}

namespace MatrixCellsInDistanceOrderTask
{

TEST(MatrixCellsInDistanceOrderTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0}, {0, 1}}), solution.allCellsDistOrder(1, 2, 0, 0));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1}, {0, 0}, {1, 1}, {1, 0}}), solution.allCellsDistOrder(2, 2, 0, 1));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2}, {0, 2}, {1, 1}, {0, 1}, {1, 0}, {0, 0}}), solution.allCellsDistOrder(2, 3, 1, 2));
}

}