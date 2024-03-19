#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums, int k) const
    {
        std::priority_queue<long long, std::vector<long long>, std::greater<long long>> numberQueue(nums.cbegin(), nums.cend());
        size_t operationCount = 0;
        while (numberQueue.top() < k)
        {
            long long x = numberQueue.top();
            numberQueue.pop();
            long long y = numberQueue.top();
            numberQueue.pop();
            numberQueue.emplace(2 * std::min(x, y) + std::max(x, y));
            ++operationCount;
        }
        return static_cast<int>(operationCount);
    }
};

}

namespace MinOpsExceedThresholdValue2Task
{

TEST(MinOpsExceedThresholdValue2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations({2, 11, 10, 1, 3}, 10));
    ASSERT_EQ(4, solution.minOperations({1, 1, 2, 4, 9}, 20));
}

TEST(MinOpsExceedThresholdValue2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations({999999999, 999999999, 999999999}, 1000000000));
}

}