#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumSize(std::vector<int> const &nums, int maxOperations) const
    {
        const size_t maxOperationsCount = maxOperations;
        const int maxValue = std::ranges::max(nums);
        if (calcOperationsCount(nums, 1) <= maxOperationsCount)
            return 1;
        int left = 1;
        int right = maxValue;
        while (left < right)
        {
            int middle = (left + right) / 2;
            if (calcOperationsCount(nums, middle) <= maxOperationsCount)
                right = middle;
            else
                left = middle + 1;
        }
        return left;
    }

private:
    [[nodiscard]] size_t calcOperationsCount(std::vector<int> const &nums, int portion) const
    {
        size_t operationsCount = 0;
        for (int number : nums)
        {
            if (number > portion)
                operationsCount += (number / portion) - ((number % portion) == 0 ? 1 : 0);
        }
        return operationsCount;
    }
};

}

namespace MinLimitOfBallsInBagTask
{

TEST(MinLimitOfBallsInBagTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumSize({9}, 2));
    ASSERT_EQ(2, solution.minimumSize({2, 4, 8, 2}, 4));
}

}