#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> kWeakestRows(std::vector<std::vector<int>> const &mat, int k) const
    {
        size_t n = mat.front().size();
        std::vector<std::vector<int>> indices(n + 1, std::vector<int>());
        for (size_t index = 0; index < mat.size(); ++index)
            indices[calcWeakness(mat[index])].push_back(static_cast<int>(index));
        std::vector<int> result;
        size_t row = 0;
        size_t index = 0;
        while (result.size() < static_cast<size_t>(k))
        {
            if (index == indices[row].size())
            {
                ++row;
                index = 0;
            }
            else
                result.push_back(indices[row][index++]);
        }
        return result;
    }

private:
    [[nodiscard]] size_t calcWeakness(std::vector<int> const &row) const
    {
        size_t result = 0;
        for (const int value : row)
        {
            if (value == 0)
                return result;
            ++result;
        }
        return result;
    }
};

}

namespace KWeakestRowsInMatrixTask
{

TEST(KWeakestRowsInMatrixTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, 0, 3}), solution.kWeakestRows({{1, 1, 0, 0, 0}, {1, 1, 1, 1, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 1, 1, 1, 1}}, 3));
    ASSERT_EQ(std::vector<int>({0, 2}), solution.kWeakestRows({{1, 0, 0, 0}, {1, 1, 1, 1}, {1, 0, 0, 0}, {1, 0, 0, 0}}, 2));
}

}