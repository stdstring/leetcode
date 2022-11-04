#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestValsFromLabels(std::vector<int> const &values, std::vector<int> const &labels, int numWanted, int useLimit) const
    {
        std::vector<size_t> indices(values.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&values](size_t left, size_t right){ return values[left] > values[right]; });
        size_t subsetSize = 0;
        int result = 0;
        constexpr int maxLabelValue = 20000;
        std::vector<size_t> labelUsage(maxLabelValue + 1, 0);
        for (const size_t index : indices)
        {
            const int label = labels[index];
            if (labelUsage[label] < static_cast<size_t>(useLimit))
            {
                ++labelUsage[label];
                result += values[index];
                ++subsetSize;
            }
            if (subsetSize == static_cast<size_t>(numWanted))
                break;
        }
        return result;
    }
};

}

namespace LargestValuesFromLabelsTask
{

TEST(LargestValuesFromLabelsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.largestValsFromLabels({5, 4, 3, 2, 1}, {1, 1, 2, 2, 3}, 3, 1));
    ASSERT_EQ(12, solution.largestValsFromLabels({5, 4, 3, 2, 1}, {1, 3, 3, 3, 2}, 3, 2));
    ASSERT_EQ(16, solution.largestValsFromLabels({9, 8, 8, 7, 6}, {0, 0, 0, 1, 1}, 3, 1));
}

}