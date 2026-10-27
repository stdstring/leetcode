#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> createGrid(int m, int n) const
    {
        std::vector<std::string> grid;
        // first row
        grid.emplace_back(n, '.');
        // other rows
        for (int row = 1; row < m; ++row)
        {
            grid.emplace_back(n, '#');
            grid.back().back() = '.';
        }
        return grid;
    }
};

}

namespace CreateGridWithExactlyOnePathTask
{

TEST(CreateGridWithExactlyOnePathTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"...", "##."}), solution.createGrid(2, 3));
    ASSERT_EQ(std::vector<std::string>({"...", "##.", "##."}), solution.createGrid(3, 3));
    ASSERT_EQ(std::vector<std::string>({"...."}), solution.createGrid(1, 4));
}

}