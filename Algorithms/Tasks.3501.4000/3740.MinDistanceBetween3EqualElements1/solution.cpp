#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumDistance(std::vector<int> const &nums) const
    {
        std::unordered_map<int, std::vector<size_t>> numbers;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            numbers[nums[index]].emplace_back(index);
        }
        size_t result = INT_MAX;
        for (const auto &[_, indexes] : numbers)
        {
            for (size_t index = 2; index < indexes.size(); ++index)
            {
                result = std::min(result, 2 * (indexes[index]  - indexes[index - 2]));
            }
        }
        return result == INT_MAX ? -1 : static_cast<int>(result);
    }
};

}

namespace MinDistanceBetween3EqualElements1Task
{

TEST(MinDistanceBetween3EqualElements1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minimumDistance({1, 2, 1, 1, 3}));
    ASSERT_EQ(8, solution.minimumDistance({1, 1, 2, 3, 2, 1, 2}));
    ASSERT_EQ(-1, solution.minimumDistance({1}));
}

}