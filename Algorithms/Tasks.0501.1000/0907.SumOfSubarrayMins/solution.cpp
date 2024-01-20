#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int sumSubarrayMins(std::vector<int> const &arr) const
    {
        // approach:
        // To arrive at the solution, we must track two things for each element arr[i]:
        // 1) left[i]: the index of the first smaller element to the left of arr[i]
        // 2) right[i] : the index of the first element that is less than or equal to arr[i] to the right
        // With left[i] and right[i] determined, the number of subarrays in which arr[i] is the minimum can be calculated by (i - left[i])* (right[i] - i).
        // init
        std::vector<int> left(arr.size(), -1);
        std::stack<size_t> leftStack;
        for (size_t index = 0; index < arr.size(); ++index)
        {
            while (!leftStack.empty() && (arr[leftStack.top()] >= arr[index]))
                leftStack.pop();
            if (!leftStack.empty())
                left[index] = static_cast<int>(leftStack.top());
            leftStack.push(index);
        }
        std::vector<int> right(arr.size(), static_cast<int>(arr.size()));
        std::stack<size_t> rightStack;
        for (size_t rIndex = 0; rIndex < arr.size(); ++rIndex)
        {
            const size_t index = arr.size() - 1 - rIndex;
            while (!rightStack.empty() && (arr[rightStack.top()] > arr[index]))
                rightStack.pop();
            if (!rightStack.empty())
                right[index] = static_cast<int>(rightStack.top());
            rightStack.push(index);
        }
        // calc
        long long subarrayMinSum = 0;
        for (size_t index = 0; index < arr.size(); ++index)
        {
            const int position = static_cast<int>(index);
            subarrayMinSum += 1LL * arr[index] * (position - left[index]) * (right[index] - position);
        }
        return static_cast<int>(subarrayMinSum % 1000000007);
    }
};

}

namespace SumOfSubarrayMinsTask
{

TEST(SumOfSubarrayMinsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(17, solution.sumSubarrayMins({3, 1, 2, 4}));
    ASSERT_EQ(444, solution.sumSubarrayMins({11, 81, 94, 43, 3}));
}

}