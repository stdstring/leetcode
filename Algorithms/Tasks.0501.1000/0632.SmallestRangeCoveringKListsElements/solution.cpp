#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> smallestRange(std::vector<std::vector<int>> const &nums) const
    {
        // prepare
        std::vector<size_t> indices(nums.size(), 0);
        std::multimap<int, size_t> currentRange;
        for (size_t index = 0; index < nums.size(); ++index)
            currentRange.emplace(nums[index][0], index);
        int rangeLeft = currentRange.cbegin()->first;
        int rangeRight = currentRange.crbegin()->first;
        int rangeSize = rangeRight - rangeLeft;
        // calc
        while (true)
        {
            size_t numbersIndex = currentRange.cbegin()->second;
            ++indices[numbersIndex];
            if (indices[numbersIndex] == nums[numbersIndex].size())
                break;
            currentRange.erase(currentRange.cbegin());
            currentRange.emplace(nums[numbersIndex][indices[numbersIndex]], numbersIndex);
            const int currentLeft = currentRange.cbegin()->first;
            const int currentRight = currentRange.crbegin()->first;
            const int currentSize = currentRight - currentLeft;
            if (currentSize < rangeSize)
            {
                rangeLeft = currentLeft;
                rangeRight = currentRight;
                rangeSize = currentSize;
            }
        }
        return {rangeLeft, rangeRight};
    }
};

}

namespace SmallestRangeCoveringKListsElementsTask
{

TEST(SmallestRangeCoveringKListsElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({20, 24}), solution.smallestRange({{4, 10, 15, 24, 26}, {0, 9, 12, 20}, {5, 18, 22, 30}}));
    ASSERT_EQ(std::vector<int>({1, 1}), solution.smallestRange({{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}));
}

}