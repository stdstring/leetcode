#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maximumTripletValue(std::vector<int> const &nums) const
    {
        std::vector<int> maxValues(nums.size(), 0);
        for (size_t rIndex = 0; rIndex < nums.size(); ++rIndex)
        {
            const size_t index = nums.size() - 1 - rIndex;
            maxValues[index] = std::max(nums[index], (rIndex == 0) ? 0 : maxValues[index + 1]);
        }
        long long bestTriplet = 0;
        int maxi = nums[0];
        for (size_t j = 1; j < nums.size() - 1; ++j)
        {
            if (maxi > nums[j])
            {
                const long long currentTriplet = 1LL * (maxi - nums[j]) * maxValues[j + 1];
                bestTriplet = std::max(bestTriplet, currentTriplet);
            }
            maxi = std::max(maxi, nums[j]);
        }
        return bestTriplet;
    }
};

}

namespace MaxValueOfOrderedTriplet1Task
{

TEST(MaxValueOfOrderedTriplet1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(77, solution.maximumTripletValue({12, 6, 1, 2, 7}));
    ASSERT_EQ(133, solution.maximumTripletValue({1, 10, 3, 4, 19}));
    ASSERT_EQ(0, solution.maximumTripletValue({1, 2, 3}));
}

}