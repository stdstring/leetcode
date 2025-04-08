#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumOperations(std::vector<int> const &nums) const
    {
        std::unordered_set<int> knownNumbers;
        for (size_t rIndex = 0; rIndex < nums.size(); ++rIndex)
        {
            const size_t index = nums.size() - 1 - rIndex;
            if (knownNumbers.contains(nums[index]))
            {
                const size_t deletedSize = index + 1;
                return static_cast<int>((deletedSize / 3) + ((deletedSize % 3) == 0 ? 0 : 1));
            }
            knownNumbers.emplace(nums[index]);
        }
        return 0;
    }
};

}

namespace MinNumberOperationsMakeArrayDistinctTask
{

TEST(MinNumberOperationsMakeArrayDistinctTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumOperations({1, 2, 3, 4, 2, 3, 3, 5, 7}));
    ASSERT_EQ(2, solution.minimumOperations({4, 5, 6, 4, 4}));
    ASSERT_EQ(0, solution.minimumOperations({6, 7, 8, 9}));
}

}