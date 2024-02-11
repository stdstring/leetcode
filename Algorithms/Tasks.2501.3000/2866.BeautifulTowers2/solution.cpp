#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maximumSumOfHeights(std::vector<int> const &maxHeights) const
    {
        // prepare
        std::vector<long long> leftSums(maxHeights.size(), 0);
        std::stack<size_t> leftStack;
        for (size_t index = 0; index < maxHeights.size(); ++index)
        {
            while (!leftStack.empty() && (maxHeights[leftStack.top()] > maxHeights[index]))
                leftStack.pop();
            const size_t currentSize = index - (leftStack.empty() ? 0 : leftStack.top()) + (leftStack.empty() ? 1 : 0);
            const long long currentSum = (leftStack.empty() ? 0 : leftSums[leftStack.top()]) +
                                         static_cast<long long>(currentSize) * maxHeights[index];
            leftSums[index] = currentSum;
            leftStack.emplace(index);
        }
        std::vector<long long> rightSums(maxHeights.size(), 0);
        std::stack<size_t> rightStack;
        for (size_t rIndex = 0; rIndex < maxHeights.size(); ++rIndex)
        {
            const size_t index = maxHeights.size() - 1 - rIndex;
            while (!rightStack.empty() && (maxHeights[rightStack.top()] > maxHeights[index]))
                rightStack.pop();
            const size_t currentSize = (rightStack.empty() ? maxHeights.size() : rightStack.top()) - index;
            const long long currentSum = (rightStack.empty() ? 0 : rightSums[rightStack.top()]) +
                                         static_cast<long long>(currentSize) * maxHeights[index];
            rightSums[index] = currentSum;
            rightStack.emplace(index);
        }
        // calculate
        long long maxSum = rightSums[0];
        const size_t maxIndex = maxHeights.size() - 1;
        for (size_t index = 0; index < maxHeights.size(); ++index)
            maxSum = std::max(maxSum, leftSums[index] + (index < maxIndex ? rightSums[index + 1] : 0));
        return maxSum;
    }
};

}

namespace BeautifulTowers2Task
{

TEST(BeautifulTowers2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.maximumSumOfHeights({5, 3, 4, 1, 1}));
    ASSERT_EQ(22, solution.maximumSumOfHeights({6, 5, 3, 9, 2, 7}));
    ASSERT_EQ(18, solution.maximumSumOfHeights({3, 2, 5, 5, 2, 3}));
}

}