#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int reinitializePermutation(int n) const
    {
        std::vector<int> permutation(n, 0);
        std::iota(permutation.begin(), permutation.end(), 0);
        size_t operationsCount = 0;
        do
        {
            applyOperation(permutation);
            ++operationsCount;
        }
        while (!checkPermutation(permutation));
        return static_cast<int>(operationsCount);
    }

private:
    void applyOperation(std::vector<int> &permutation) const
    {
        std::vector<int> next(permutation.size(), 0);
        for (size_t index = 0; index < next.size(); ++index)
        {
            if ((index % 2) == 0)
                next[index] = permutation[index / 2];
            else
                next[index] = permutation[permutation.size() / 2 + (index - 1) / 2];
        }
        std::swap(permutation, next);
    }

    [[nodiscard]] bool checkPermutation(std::vector<int> const &permutation) const
    {
        for (size_t rIndex = 0; rIndex < permutation.size(); ++rIndex)
        {
            const size_t index = permutation.size() - 1 - rIndex;
            const int number = static_cast<int>(permutation.size() - 1 - rIndex);
            if (permutation[index] != number)
                return false;
        }
        return true;
    }
};

}

namespace MinNumberOpToReinitPermutationTask
{

TEST(MinNumberOpToReinitPermutationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.reinitializePermutation(2));
    ASSERT_EQ(2, solution.reinitializePermutation(4));
    ASSERT_EQ(4, solution.reinitializePermutation(6));
}

TEST(MinNumberOpToReinitPermutationTaskTests, Custom)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.reinitializePermutation(8));
    ASSERT_EQ(99, solution.reinitializePermutation(200));
    ASSERT_EQ(36, solution.reinitializePermutation(1000));
}

}