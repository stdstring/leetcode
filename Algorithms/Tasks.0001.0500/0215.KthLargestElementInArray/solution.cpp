#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findKthLargestViaSorting(std::vector<int> const &nums, int k) const
    {
        std::vector<int> result(nums);
        std::sort(result.begin(), result.end());
        return result[nums.size() - k];
    }

    int findKthLargestViaPriorityQueue(std::vector<int> const& nums, int k) const
    {
        const size_t queueSize = k;
        std::priority_queue<int, std::vector<int>, std::greater<>> numbersQueue;
        for (int number : nums)
        {
            if (numbersQueue.size() < queueSize || number > numbersQueue.top())
                numbersQueue.push(number);
            if (numbersQueue.size() > queueSize)
                numbersQueue.pop();
        }
        return numbersQueue.top();
    }
};

}

namespace KthLargestElementInArrayTask
{

TEST(KthLargestElementInArrayTaskTests, ExamplesViaSorting)
{
    const Solution solution;
    ASSERT_EQ(5, solution.findKthLargestViaSorting({3, 2, 1, 5, 6, 4}, 2));
    ASSERT_EQ(4, solution.findKthLargestViaSorting({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4));
}

TEST(KthLargestElementInArrayTaskTests, ExamplesViaPriorityQueue)
{
    const Solution solution;
    ASSERT_EQ(5, solution.findKthLargestViaPriorityQueue({ 3, 2, 1, 5, 6, 4 }, 2));
    ASSERT_EQ(4, solution.findKthLargestViaPriorityQueue({ 3, 2, 3, 1, 2, 4, 5, 5, 6 }, 4));
}

}