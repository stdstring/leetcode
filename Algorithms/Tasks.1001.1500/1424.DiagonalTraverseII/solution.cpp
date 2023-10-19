#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findDiagonalOrder(std::vector<std::vector<int>> const &nums) const
    {
        std::vector<std::pair<size_t, size_t>> cells;
        for (size_t row = 0; row < nums.size(); ++row)
        {
            for (size_t column = 0; column < nums[row].size(); ++column)
                cells.emplace_back(row, column);
        }
        auto comp = [](std::pair<size_t, size_t> const &l, std::pair<size_t, size_t> const &r)
        {
            const size_t lSum = l.first + l.second;
            const size_t rSum = r.first + r.second;
            return (lSum < rSum) || ((lSum == rSum) && (l.first > r.first));
        };
        std::ranges::sort(cells, comp);
        std::vector<int> result(cells.size(), 0);
        for (size_t index = 0; index < cells.size(); ++index)
            result[index] = nums[cells[index].first][cells[index].second];
        return result;
    }
};

}

namespace DiagonalTraverseIITask
{

TEST(DiagonalTraverseIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 4, 2, 7, 5, 3, 8, 6, 9}),
                               solution.findDiagonalOrder({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    ASSERT_EQ(std::vector<int>({1, 6, 2, 8, 7, 3, 9, 4, 12, 10, 5, 13, 11, 14, 15, 16}),
                               solution.findDiagonalOrder({{1, 2, 3, 4, 5}, {6, 7}, {8}, {9, 10, 11}, {12, 13, 14, 15, 16}}));
}

}