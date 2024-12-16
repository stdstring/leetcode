#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getFinalState(std::vector<int> const &nums, int k, int multiplier) const
    {
        std::vector<int> result(nums);
        auto cmp = [&result](size_t l, size_t r) { return !((result[l] < result[r]) || ((result[l] == result[r]) && (l < r))); };
        std::priority_queue<size_t, std::vector<size_t>, decltype(cmp)> numberQueue(cmp);
        for (size_t index = 0; index < result.size(); ++index)
            numberQueue.emplace(index);
        for (int operation = 1; operation <= k; ++operation)
        {
            size_t index = numberQueue.top();
            numberQueue.pop();
            result[index] *= multiplier;
            numberQueue.push(index);
        }
        return result;
    }
};

}

namespace FinalArrayStateAfterKMultOps1Task
{

TEST(FinalArrayStateAfterKMultOps1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({8, 4, 6, 5, 6}), solution.getFinalState({2, 1, 3, 5, 6}, 5, 2));
    ASSERT_EQ(std::vector<int>({16, 8}), solution.getFinalState({1, 2}, 3, 4));
}

}