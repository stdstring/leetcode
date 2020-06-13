#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> getRow(int rowIndex) const
    {
        if (rowIndex == 0)
            return {1};
        if (rowIndex == 1)
            return {1, 1};
        std::vector<int> result = {1, 1};
        for (int row = 2; row <= rowIndex; ++row)
        {
            int current = 1;
            for (int column = 1; column < row; ++column)
            {
                const int value = current + result[column];
                current = result[column];
                result[column] = value;
            }
            result.push_back(1);
        }
        return result;
    }
};

}

namespace PascalTriangleIITask
{

TEST(PascalTriangleIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 3, 1}), solution.getRow(3));
}

}