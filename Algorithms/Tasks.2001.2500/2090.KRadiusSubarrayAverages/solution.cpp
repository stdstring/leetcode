#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getAverages(std::vector<int> const &nums, int k) const
    {
        const size_t windowSize = 2 * k + 1;
        const size_t startIndex = windowSize - 1;
        std::vector<int> averages(nums.size(), -1);
        long long windowSum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (index > startIndex)
                windowSum -= nums[index - windowSize];
            windowSum += nums[index];
            if (index >= startIndex)
                averages[index - k] = static_cast<int>(windowSum / windowSize);
        }
        return averages;
    }
};

}

namespace KRadiusSubarrayAveragesTask
{

TEST(KRadiusSubarrayAveragesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({-1, -1, -1, 5, 4, 4, -1, -1, -1}), solution.getAverages({7, 4, 3, 9, 1, 8, 5, 2, 6}, 3));
    ASSERT_EQ(std::vector<int>({100000}), solution.getAverages({100000}, 0));
    ASSERT_EQ(std::vector<int>({-1}), solution.getAverages({8}, 100000));
}

}