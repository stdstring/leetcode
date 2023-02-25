#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxRotateFunction(std::vector<int> const &A) const
    {
        int result = calcInitValue(A);
        long long elementSum = 0;
        for (int element : A)
            elementSum += element;
        long long value = result;
        for (size_t index = 1; index < A.size(); ++index)
        {
            value = value + elementSum - A.size() * A[A.size() - index];
            result = std::max(result, static_cast<int>(value));
        }
        return result;
    }

private:
    int calcInitValue(std::vector<int> const &A) const
    {
        int value = 0;
        for (size_t index = 1; index < A.size(); ++index)
            value += static_cast<int>(index) * A[index];
        return value;
    }
};

}

namespace RotateFunctionTask
{

TEST(RotateFunctionTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(26, solution.maxRotateFunction({4, 3, 2, 6}));
}

TEST(RotateFunctionTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2147483647, solution.maxRotateFunction({2147483647, 2147483647}));
}

}