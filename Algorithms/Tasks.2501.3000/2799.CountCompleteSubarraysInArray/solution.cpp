#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countCompleteSubarrays(std::vector<int> const &nums) const
    {
        const std::unordered_set<int> totalNums(nums.cbegin(), nums.cend());
        const size_t totalDistinctCount = totalNums.size();
        std::unordered_map<int, size_t> slidingWindow;
        size_t result = 0;
        for (size_t start = 0, end = 0; end < nums.size(); ++end)
        {
            ++slidingWindow[nums[end]];
            while (slidingWindow.size() == totalDistinctCount)
            {
                result += (nums.size() - end);
                if (slidingWindow[nums[start]] == 1)
                    slidingWindow.erase(nums[start]);
                else
                    --slidingWindow[nums[start]];
                ++start;
            }
        }
        return static_cast<int>(result);
    }
};

}

namespace CountCompleteSubarraysInArrayTask
{

TEST(CountCompleteSubarraysInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countCompleteSubarrays({1, 3, 1, 2, 2}));
    ASSERT_EQ(10, solution.countCompleteSubarrays({5, 5, 5, 5}));
}

}