#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int stoneGameVIII(std::vector<int> const &stones) const
    {
        // Bottom-Up dynamic programming
        std::vector<int> prefixSums(stones.size(), 0);
        for (size_t index = 0; index < stones.size(); ++index)
            prefixSums[index] = stones[index] + ((index > 0) ? prefixSums[index - 1] : 0);
        int result = prefixSums.back();
        for (size_t rIndex = 1; rIndex < prefixSums.size() - 1; ++rIndex)
        {
            const size_t index = prefixSums.size() - 1 - rIndex;
            result = std::max(result, prefixSums[index] - result);
        }
        return result;
    }
};

}

namespace StoneGameVIIITask
{

TEST(StoneGameVIIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.stoneGameVIII({-1, 2, -3, 4, -5}));
    ASSERT_EQ(13, solution.stoneGameVIII({7, -6, 5, 10, 5, -2, -6}));
    ASSERT_EQ(-22, solution.stoneGameVIII({-10, -12}));
}

}