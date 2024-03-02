#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSumOfLengths(std::vector<int> const &arr, int target) const
    {
        // prepare data
        std::vector<int> prefixMinSize(arr.size(), -1);
        std::unordered_map<int, size_t> prefixSumMap;
        int prefixSum = 0;
        std::vector<int> suffixMinSize(arr.size(), -1);
        std::unordered_map<int, size_t> suffixSumMap;
        int suffixSum = 0;
        for (size_t index = 0; index < arr.size(); ++index)
        {
            // prefix
            prefixSum += arr[index];
            if (index > 0)
                prefixMinSize[index] = prefixMinSize[index - 1];
            if (arr[index] == target)
                prefixMinSize[index] = 1;
            preparePortionMinSize(prefixSum, target, prefixSumMap, prefixMinSize, index, index + 1);
            // suffix
            const size_t rIndex = arr.size() - 1 - index;
            suffixSum += arr[rIndex];
            if (index > 0)
                suffixMinSize[rIndex] = suffixMinSize[rIndex + 1];
            if (arr[rIndex] == target)
                suffixMinSize[rIndex] = 1;
            preparePortionMinSize(suffixSum, target, suffixSumMap, suffixMinSize, rIndex, index + 1);
        }
        // calc
        int minLength = -1;
        for (size_t index = 0; index < arr.size() - 1; ++index)
        {
            const int prefixMinLength = prefixMinSize[index];
            const int suffixMinLength = suffixMinSize[index + 1];
            if (suffixMinLength == -1)
                break;
            if (prefixMinLength == -1)
                continue;
            minLength = std::min(prefixMinLength + suffixMinLength, minLength == -1 ? INT_MAX : minLength);
        }
        return minLength;
    }

private:
    void preparePortionMinSize(int portionSum,
                               int target,
                               std::unordered_map<int, size_t> &portionSumMap,
                               std::vector<int> &portionMinSize,
                               size_t index,
                               size_t portionSize) const
    {
        portionSumMap.emplace(portionSum, index);
        if (portionMinSize[index] == 1)
            return;
        if (portionSum == target)
        {
            portionMinSize[index] = std::min(static_cast<int>(portionSize), portionMinSize[index] == -1 ? INT_MAX : portionMinSize[index]);
            return;
        }
        const auto iterator = portionSumMap.find(portionSum - target);
        if (iterator == portionSumMap.cend())
            return;
        const int length = static_cast<int>(index > iterator->second ? index - iterator->second : iterator->second - index);
        portionMinSize[index] = std::min(length, portionMinSize[index] == -1 ? INT_MAX : portionMinSize[index]);
    }
};

}

namespace Find2NonOverlappingSubarraysWithTargetSumTask
{

TEST(Find2NonOverlappingSubarraysWithTargetSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minSumOfLengths({3, 2, 2, 4, 3}, 3));
    ASSERT_EQ(2, solution.minSumOfLengths({7, 3, 4, 7}, 7));
    ASSERT_EQ(-1, solution.minSumOfLengths({4, 3, 2, 6, 2, 3, 4}, 6));
}

TEST(Find2NonOverlappingSubarraysWithTargetSumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minSumOfLengths({3, 1, 1, 1, 5, 1, 2, 1}, 3));
}

}