#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void duplicateZeros(std::vector<int> &arr)
    {
        if (arr.size() == 1)
            return;
        size_t fromIndex = 0;
        size_t shift = 0;
        while (fromIndex + shift < arr.size())
        {
            if (arr[fromIndex] == 0)
                ++shift;
            ++fromIndex;
        }
        if (shift == 0)
            return;
        const bool lastFull = fromIndex + shift == arr.size();
        --fromIndex;
        size_t toIndex = arr.size() - 1;
        while (fromIndex < toIndex)
        {
            arr[toIndex] = arr[fromIndex];
            if (arr[toIndex] == 0 && (toIndex < arr.size() - 1 || lastFull))
                arr[--toIndex] = 0;
            --fromIndex;
            --toIndex;
        }
    }
};

}

namespace
{

void checkDuplicateZeros(std::vector<int> const &source, std::vector<int> const &expectedResult)
{
    Solution solution;
    std::vector<int> data(source);
    solution.duplicateZeros(data);
    ASSERT_EQ(expectedResult, data);
}

}

namespace DuplicateZerosTask
{

TEST(DuplicateZerosTaskTests, Examples)
{
    checkDuplicateZeros({1, 0, 2, 3, 0, 4, 5, 0}, {1, 0, 0, 2, 3, 0, 0, 4});
    checkDuplicateZeros({1, 2, 3}, {1, 2, 3});
}

TEST(DuplicateZerosTaskTests, FromWrongAnswers)
{
    checkDuplicateZeros({1, 2, 0, 0, 1, 0, 3, 4}, {1, 2, 0, 0, 0, 0, 1, 0});
    checkDuplicateZeros({1, 5, 2, 0, 6, 8, 0, 6, 0}, {1, 5, 2, 0, 0, 6, 8, 0, 0});
}

}