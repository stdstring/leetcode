#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countBadPairs(std::vector<int> const &nums) const
    {
        // A pair of indices (i, j) is a bad pair if i < j and j - i != nums[j] - nums[i].
        // j - i != nums[j] - nums[i] => nums[j] - j != nums[i] - i
        std::unordered_map<int, size_t> diffMap;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const int diff = nums[index] - static_cast<int>(index);
            ++diffMap[diff];
        }
        size_t pairsCount = 0;
        for (auto [_, count] : diffMap)
            pairsCount += (count * (nums.size() - count));
        return static_cast<long long>(pairsCount / 2);
    }
};

}

namespace CountNumberBadPairsTask
{

TEST(CountNumberBadPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.countBadPairs({4, 1, 3, 3}));
    ASSERT_EQ(0, solution.countBadPairs({1, 2, 3, 4, 5}));
}

}