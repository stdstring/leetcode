#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> matrixReshape(std::vector<std::vector<int>> const &nums, int r, int c) const
    {
        if (static_cast<size_t>(r * c) != (nums.size() * nums[0].size()))
            return nums;
        std::vector<std::vector<int>> dest(r, std::vector<int>(c, 0));
        for (size_t rowIndex = 0; rowIndex < nums.size(); ++rowIndex)
        {
            for (size_t columnIndex = 0; columnIndex < nums[0].size(); ++columnIndex)
            {
                const size_t linearIndex = rowIndex * nums[0].size() + columnIndex;
                dest[linearIndex / c][linearIndex % c] = nums[rowIndex][columnIndex];
            }
        }
        return dest;
    }
};

}

namespace ReshapeMatrixTask
{

TEST(ReshapeMatrixTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 3, 4}}), solution.matrixReshape({{1, 2}, {3, 4}}, 1, 4));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2}, {3, 4}}), solution.matrixReshape({{1, 2}, {3, 4}}, 2, 4));
}

}