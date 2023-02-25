#include <deque>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> maxSlidingWindow(std::vector<int> const &nums, int k) const
    {
        std::vector<int> dest;
        std::deque<int> maxQueue;
        // init fill maxQueue
        for (size_t index = 0; index < k; ++index)
            appendElementToMaxQueue(maxQueue, nums[index]);
        dest.push_back(maxQueue.front());
        // move window
        for (size_t index = k; index < nums.size(); ++index)
        {
            if (maxQueue.front() == nums[index - k])
                maxQueue.pop_front();
            appendElementToMaxQueue(maxQueue, nums[index]);
            dest.push_back(maxQueue.front());
        }
        return dest;
    }

private:
    void appendElementToMaxQueue(std::deque<int> &maxQueue, int element) const
    {
        while (!maxQueue.empty() && maxQueue.back() < element)
            maxQueue.pop_back();
        maxQueue.push_back(element);
    }
};

}

namespace SlidingWindowMaximumTask
{

TEST(SlidingWindowMaximumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3, 3, 5, 5, 6, 7}), solution.maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3));
}

TEST(SlidingWindowMaximumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, -1}), solution.maxSlidingWindow({1, -1}, 1));
}

}