#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> smallestSubarrays(std::vector<int> const &nums) const
    {
        // 10^9 < 2^30
        constexpr int bitCount = 31;
        std::vector<std::queue<size_t>> bitIndices(bitCount);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            for (int bit = 0; bit < bitCount; ++bit)
            {
                const int mask = 1 << bit;
                if ((nums[index] & mask) != 0)
                    bitIndices[bit].emplace(index);
            }
        }
        std::vector<int> result(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            size_t maxIndex = index;
            for (int bit = 0; bit < bitCount; ++bit)
            {
                if (bitIndices[bit].empty())
                    continue;
                maxIndex = std::max(maxIndex, bitIndices[bit].front());
                if (bitIndices[bit].front() == index)
                    bitIndices[bit].pop();
            }
            result[index] = static_cast<int>(maxIndex - index + 1);
        }
        return result;
    }
};

}

namespace SmallestSubarraysWithMaxBitwiseORTask
{

TEST(SmallestSubarraysWithMaxBitwiseORTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 3, 2, 2, 1}), solution.smallestSubarrays({1, 0, 2, 1, 3}));
    ASSERT_EQ(std::vector<int>({2, 1}), solution.smallestSubarrays({1, 2}));
}

}