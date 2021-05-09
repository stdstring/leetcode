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
        size_t chunkCount = 0;
        int maxValue = 0;
        for (int index = 0; index < static_cast<int>(arr.size()); ++index)
        {
            maxValue = std::max(maxValue, arr[index]);
            if (maxValue == index)
                ++chunkCount;
        }
        return static_cast<int>(chunkCount);
    }
};

}

namespace MaxChunksToMakeSortedTask
{

TEST(MaxChunksToMakeSortedTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.maxChunksToSorted({4, 3, 2, 1, 0}));
    ASSERT_EQ(4, solution.maxChunksToSorted({1, 0, 2, 3, 4}));
}

}