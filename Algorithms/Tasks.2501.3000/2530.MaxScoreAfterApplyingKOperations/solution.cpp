#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxKelementsViaPriorityQueue(std::vector<int> const &nums, int k) const
    {
        std::priority_queue<int> queue;
        for (int number : nums)
            queue.push(number);
        long long result = 0;
        for (int step = 0; step < k; ++step)
        {
            result += queue.top();
            std::cout << queue.top() << std::endl;
            queue.push(queue.top() / 3 + (queue.top() % 3 > 0 ? 1 : 0));
            queue.pop();
        }
        return result;
    }

    [[nodiscard]] long long maxKelementsViaComplexApproach(std::vector<int> const &nums, int k) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end(), std::greater<>());
        std::queue<int> queue;
        long long result = 0;
        size_t numbersIndex = 0;
        for (int step = 0; step < k; ++step)
        {
            if (numbersIndex < numbers.size() && (queue.empty() || numbers[numbersIndex] > queue.front()))
            {
                result += numbers[numbersIndex];
                queue.push(numbers[numbersIndex] / 3 + (numbers[numbersIndex] % 3 > 0 ? 1 : 0));
                ++numbersIndex;
            }
            else
            {
                result += queue.front();
                queue.push(queue.front() / 3 + (queue.front() % 3 > 0 ? 1 : 0));
                queue.pop();
            }
        }
        return result;
    }
};

}

namespace
{

void checkMaxKelements(std::vector<int> const &nums, int k, long long expectedValue)
{
    constexpr Solution solution;
    ASSERT_EQ(expectedValue, solution.maxKelementsViaPriorityQueue(nums, k));
    ASSERT_EQ(expectedValue, solution.maxKelementsViaComplexApproach(nums, k));
}

}

namespace MaxScoreAfterApplyingKOperationsTask
{

TEST(MaxScoreAfterApplyingKOperationsTaskTests, Examples)
{
    checkMaxKelements({10, 10, 10, 10, 10}, 5,50);
    checkMaxKelements({1, 10, 3, 3, 3}, 3, 17);
}

}