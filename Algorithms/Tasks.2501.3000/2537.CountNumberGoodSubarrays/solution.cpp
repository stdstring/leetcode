#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countGood(std::vector<int> const &nums, int k) const
    {
        const long long minPairCount = k;
        long long currentPairCount = 0;
        std::unordered_map<int, int> slidingWindow;
        size_t start = 0;
        size_t result = 0;
        // before reaching of end
        for (size_t end = 0; end < nums.size(); ++end)
        {
            const int number = nums[end];
            ++slidingWindow[number];
            const int numberCount = slidingWindow[number];
            currentPairCount += (numberCount - 1);
            while (currentPairCount >= minPairCount)
            {
                result += (nums.size() - end);
                const int startNumber = nums[start];
                const int startNumberCount = slidingWindow[startNumber];
                currentPairCount -= (startNumberCount - 1);
                --slidingWindow[startNumber];
                ++start;
            }
        }
        // reaching of end
        while (currentPairCount >= minPairCount)
        {
            ++result;
            const int startNumber = nums[start];
            const int startNumberCount = slidingWindow[startNumber];
            currentPairCount -= (startNumberCount - 1);
            --slidingWindow[startNumber];
            ++start;
        }
        return static_cast<long long>(result);
    }
};

}

namespace CountNumberGoodSubarraysTask
{

TEST(CountNumberGoodSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.countGood({1, 1, 1, 1, 1}, 10));
    ASSERT_EQ(4, solution.countGood({3, 1, 4, 3, 2, 2, 4}, 2));
}

}