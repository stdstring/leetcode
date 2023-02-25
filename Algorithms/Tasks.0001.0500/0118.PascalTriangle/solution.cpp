#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> generate(int numRows) const
    {
        std::vector<std::vector<int>> dest;
        dest.reserve(numRows);
        if (numRows == 0)
            return dest;
        dest.push_back({1});
        if (numRows == 1)
            return dest;
        dest.push_back({1, 1});
        if (numRows == 2)
            return dest;
        for(int row = 3; row <= numRows; ++row)
        {
            std::vector<int> current;
            current.reserve(row);
            current.push_back(1);
            for(int column = 1; column < row - 1; ++column)
                current.push_back(dest.back()[column - 1] + dest.back()[column]);
            current.push_back(1);
            dest.push_back(current);
        }
        return dest;
    }
};

}

namespace PascalTriangleTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1}, {1,1}, {1,2,1}, {1,3,3,1}, {1,4,6,4,1}}), solution.generate(5));
}

}