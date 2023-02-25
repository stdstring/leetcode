#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSetSize(std::vector<int> const &arr) const
    {
        constexpr int maxValue = 100000;
        std::vector<size_t> counts(maxValue, 0);
        for (const int number : arr)
            ++counts[static_cast<size_t>(number) - 1];
        std::sort(counts.begin(), counts.end(), std::greater<int>());
        size_t setSize = 0;
        for (size_t index = 0, removedCount = 0; removedCount < arr.size() / 2; ++index)
        {
            removedCount += counts[index];
            ++setSize;
        }
        return static_cast<int>(setSize);
    }
};

}

namespace ReduceArraySizeToHalfTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minSetSize({3, 3, 3, 3, 5, 5, 5, 2, 2, 7}));
    ASSERT_EQ(1, solution.minSetSize({7, 7, 7, 7, 7, 7}));
}

}