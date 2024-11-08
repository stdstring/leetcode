#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getMaximumXor(std::vector<int> const &nums, int maximumBit) const
    {
        std::vector<int> answer(nums.size(), 0);
        int prefixXor = std::accumulate(nums.cbegin(), nums.cend(), 0, [](int acc, int value){ return acc ^ value; });
        for (size_t rIndex = 0; rIndex < nums.size(); ++rIndex)
        {
            size_t index = nums.size() - 1 - rIndex;
            answer[rIndex] = calcMaxK(prefixXor, maximumBit);
            prefixXor ^= nums[index];
        }
        return answer;
    }

private:
    [[nodiscard]] int calcMaxK(int xorValue, int maximumBit) const
    {
        int k = 0;
        for (int bit = 0; bit < maximumBit; ++bit)
        {
            int mask = 1 << bit;
            if ((xorValue & mask) == 0)
                k |= mask;
        }
        return k;
    }
};

}

namespace MaxXorForEachQueryTask
{

TEST(MaxXorForEachQueryTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 3, 2, 3}), solution.getMaximumXor({0, 1, 1, 3}, 2));
    ASSERT_EQ(std::vector<int>({5, 2, 6, 5}), solution.getMaximumXor({2, 3, 4, 7}, 3));
    ASSERT_EQ(std::vector<int>({4, 3, 6, 4, 6, 7}), solution.getMaximumXor({0, 1, 2, 2, 5, 7}, 3));
}

}