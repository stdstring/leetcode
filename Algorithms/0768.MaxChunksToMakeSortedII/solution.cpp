#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxChunksToSorted(std::vector<int> const &arr) const
    {
        std::vector<int> suffixMinValue(arr.size(), 0);
        for (size_t index = 0; index < arr.size(); ++index)
        {
            const size_t revIndex = arr.size() - 1 - index;
            suffixMinValue[revIndex] = index == 0 ? arr[revIndex] : std::min(arr[revIndex], suffixMinValue[revIndex + 1]);
        }
        size_t chunksCount = 0;
        int maxValue = 0;
        for (size_t index = 0; index < arr.size(); ++index)
        {
            maxValue = index == 0 ? arr[index] : std::max(maxValue, arr[index]);
            if ((index == arr.size() - 1) || (maxValue <= suffixMinValue[index + 1]))
                ++chunksCount;
        }
        return static_cast<int>(chunksCount);
    }
};

}

namespace MaxChunksToMakeSortedIITask
{

TEST(MaxChunksToMakeSortedIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.maxChunksToSorted({5, 4, 3, 2, 1}));
    ASSERT_EQ(4, solution.maxChunksToSorted({2, 1, 3, 4, 4}));
}

}