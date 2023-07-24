#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minIncrements(int n, std::vector<int> const &cost) const
    {
        return processTree(cost, 1).second;
    }

private:
    // total cost, increment count
    [[nodiscard]] std::pair<int, int> processTree(std::vector<int> const &cost, int current) const
    {
        const size_t index = current - 1;
        if (index >= cost.size())
            return {0, 0};
        const std::pair<int, int> leftResult(processTree(cost, 2 * current));
        const std::pair<int, int> rightResult(processTree(cost, 2 * current + 1));
        int totalCost = cost[index] + std::max(leftResult.first, rightResult.first);
        int incrementCount = std::abs(leftResult.first - rightResult.first) + leftResult.second + rightResult.second;
        return {totalCost, incrementCount};
    }
};

}

namespace MakeCostsOfPathsEqualInBinaryTreeTask
{

TEST(MakeCostsOfPathsEqualInBinaryTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minIncrements(7, {1, 5, 2, 2, 3, 3, 1}));
    ASSERT_EQ(0, solution.minIncrements(3, {5, 3, 3}));
}

}