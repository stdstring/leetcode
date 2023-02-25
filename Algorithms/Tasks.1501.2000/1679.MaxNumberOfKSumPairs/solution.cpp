#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxOperations(std::vector<int> const &nums, int k) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        size_t count = 0;
        for (size_t left = 0, right = numbers.size() - 1; left < right;)
        {
            const int sum = numbers[left] + numbers[right];
            if (sum <= k)
                ++left;
            if (sum >= k)
                --right;
            if (sum == k)
                ++count;
        }
        return static_cast<int>(count);
    }
};

}

namespace MaxNumberOfKSumPairsTask
{

TEST(MaxNumberOfKSumPairsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.maxOperations({1, 2, 3, 4}, 5));
    ASSERT_EQ(1, solution.maxOperations({3, 1, 3, 4, 3}, 6));
}

}