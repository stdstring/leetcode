#include <algorithm>
#include <bitset>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumSubarrayLength(std::vector<int> const &nums, int k) const
    {
        if (k == 0)
            return 1;
        std::vector<int> frequencies(32, 0);
        int bestLength = INT_MAX;
        for (size_t left = 0, right = 0; right < nums.size(); ++right)
        {
            if (nums[right] >= k)
                return 1;
            addNumber(frequencies, nums[right]);
            while ((left < right) && checkSubarray(frequencies, k))
            {
                bestLength = std::min(bestLength, static_cast<int>(right - left + 1));
                removeNumber(frequencies, nums[left]);
                ++left;
            }
        }
        return bestLength == INT_MAX ? - 1 : bestLength;
    }

private:
    [[nodiscard]] bool checkSubarray(std::vector<int> const &frequencies, int k) const
    {
        int result = 0;
        int mask = 1;
        for (int frequency : frequencies)
        {
            if (frequency > 0)
                result |= mask;
            mask <<= 1;
        }
        return result >= k;
    }

    void addNumber(std::vector<int> &frequencies, int number) const
    {
        std::bitset<32> bits(number);
        for (size_t index = 0; index < bits.size(); ++index)
            frequencies[index] += bits[index];
    }

    void removeNumber(std::vector<int> &frequencies, int number) const
    {
        std::bitset<32> bits(number);
        for (size_t index = 0; index < bits.size(); ++index)
            frequencies[index] -= bits[index];
    }
};

}

namespace ShortestSubarrayWithOrAtLeastK2Task
{

TEST(ShortestSubarrayWithOrAtLeastK2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minimumSubarrayLength({1, 2, 3}, 2));
    ASSERT_EQ(3, solution.minimumSubarrayLength({2, 1, 8}, 10));
    ASSERT_EQ(1, solution.minimumSubarrayLength({1, 2}, 0));
}

}