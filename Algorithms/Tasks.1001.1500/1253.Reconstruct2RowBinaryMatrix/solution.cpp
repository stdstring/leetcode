#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> reconstructMatrix(int upper, int lower, std::vector<int> const &colsum) const
    {
        std::vector<std::vector<int>> matrix(2, std::vector<int>(colsum.size(), 0));
        for (size_t index = 0; index < colsum.size(); ++index)
        {
            if (colsum[index] == 2)
            {
                if ((upper == 0) || (lower == 0))
                    return {};
                matrix[0][index] = matrix[1][index] = 1;
                --upper;
                --lower;
            }
        }
        for (size_t index = 0; index < colsum.size(); ++index)
        {
            if (colsum[index] == 1)
            {
                if (upper > 0)
                {
                    matrix[0][index] = 1;
                    --upper;
                }
                else if (lower > 0)
                {
                    matrix[1][index] = 1;
                    --lower;
                }
                else
                    return {};
            }
        }
        return (upper == 0) && (lower == 0) ? matrix : std::vector<std::vector<int>>();
    }
};

}

namespace Reconstruct2RowBinaryMatrixTask
{

TEST(Reconstruct2RowBinaryMatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1, 0}, {0, 0, 1}}),
              solution.reconstructMatrix(2, 1, {1, 1, 1}));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.reconstructMatrix(2, 3, {2, 2, 1, 1}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1, 1, 0, 1, 0, 0, 1, 0, 0}, {1, 0, 1, 0, 0, 0, 1, 1, 0, 1}}),
              solution.reconstructMatrix(5, 5, {2, 1, 2, 0, 1, 0, 1, 2, 0, 1}));
}

}