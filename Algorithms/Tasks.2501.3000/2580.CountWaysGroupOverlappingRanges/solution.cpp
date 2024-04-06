#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countWays(std::vector<std::vector<int>> const &ranges) const
    {
        std::vector<std::vector<int>> sortedRanges(ranges);
        std::ranges::sort(sortedRanges, [](std::vector<int> const &l, std::vector<int> const &r){ return l[0] < r[0]; });
        std::vector<std::vector<int>> destRanges;
        destRanges.reserve(sortedRanges.size());
        for (std::vector<int> const &range : sortedRanges)
        {
            if (!destRanges.empty() && (range[0] <= destRanges.back()[1]))
                destRanges.back()[1] = std::max(destRanges.back()[1], range[1]);
            else
                destRanges.emplace_back(range);
        }
        // C(0,n) + C(1,n) + ... C(n,n) = 2^n
        constexpr size_t modValue = 1000000007;
        size_t result = 1;
        for (size_t index = 0; index < destRanges.size(); ++index)
            result = (2 * result) % modValue;
        return static_cast<int>(result);
    }
};

}

namespace CountWaysGroupOverlappingRangesTask
{

TEST(CountWaysGroupOverlappingRangesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countWays({{6, 10}, {5, 15}}));
    ASSERT_EQ(4, solution.countWays({{1, 3}, {10, 20}, {2, 5}, {4, 8}}));
}

TEST(CountWaysGroupOverlappingRangesTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(64, solution.countWays({{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}, {11, 12}}));
}

}