#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int sumCounts(std::vector<int> const &nums) const
    {
        int result = 0;
        for (size_t start = 0; start < nums.size(); ++start)
        {
            std::set<int> distinctNumbers;
            for (size_t end  = start; end < nums.size(); ++end)
            {
                distinctNumbers.emplace(nums[end]);
                const int distinctCount = static_cast<int>(distinctNumbers.size());
                result += distinctCount * distinctCount;
            }
        }
        return result;
    }
};

}

namespace SubarraysDistinctElementSquaresSum1Task
{

TEST(SubarraysDistinctElementSquaresSum1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.sumCounts({1, 2, 1}));
    ASSERT_EQ(3, solution.sumCounts({1, 1}));
}

}