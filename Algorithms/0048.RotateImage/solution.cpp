#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void rotate(std::vector<std::vector<int>> &matrix)
    {
        const int n = matrix.size();
        int minIndex = 0;
        int maxIndex = n - 1;
        while (minIndex < maxIndex)
        {
            for (int shift = 0; shift < maxIndex - minIndex; ++shift)
            {
                const int value1 = matrix[minIndex][minIndex + shift];
                const int value2 = matrix[minIndex + shift][maxIndex];
                const int value3 = matrix[maxIndex][maxIndex - shift];
                const int value4 = matrix[maxIndex - shift][minIndex];
                matrix[minIndex + shift][maxIndex] = value1;
                matrix[maxIndex][maxIndex - shift] = value2;
                matrix[maxIndex - shift][minIndex] = value3;
                matrix[minIndex][minIndex + shift] = value4;
            }
            ++minIndex;
            --maxIndex;
        }
    }
};

}

namespace RotateImageTask
{

TEST(RotateImageTaskTests, Examples)
{
    Solution solution;
    std::vector<std::vector<int>> matrix1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    solution.rotate(matrix1);
    ASSERT_EQ(std::vector<std::vector<int>>({{7, 4, 1}, {8, 5, 2}, {9, 6, 3}}), matrix1);
    std::vector<std::vector<int>> matrix2({{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}});
    solution.rotate(matrix2);
    ASSERT_EQ(std::vector<std::vector<int>>({{15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}}), matrix2);
}

}