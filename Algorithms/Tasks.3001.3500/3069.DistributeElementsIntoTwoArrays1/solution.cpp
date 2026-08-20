#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> resultArray(std::vector<int> const &nums) const
    {
        std::vector<int> first;
        first.reserve(nums.size());
        std::vector<int> second;
        second.reserve(nums.size());
        first.emplace_back(nums[0]);
        second.emplace_back(nums[1]);
        for (size_t index = 2; index < nums.size(); ++index)
            (first.back() > second.back() ? first : second).emplace_back(nums[index]);
        std::vector<int> result;
        result.reserve(nums.size());
        std::ranges::copy(std::as_const(first), std::back_inserter(result));
        std::ranges::copy(std::as_const(second), std::back_inserter(result));
        return result;
    }
};

}

namespace DistributeElementsIntoTwoArrays1Task
{

TEST(DistributeElementsIntoTwoArrays1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 3, 1}), solution.resultArray({2, 1, 3}));
    ASSERT_EQ(std::vector<int>({5, 3, 4, 8}), solution.resultArray({5, 4, 3, 8}));
}

}