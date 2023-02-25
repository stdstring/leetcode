#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findRightInterval(std::vector<std::vector<int>> const &intervals) const
    {
        std::map<int, size_t> leftIndices;
        for (size_t index = 0; index < intervals.size(); ++index)
            leftIndices.emplace(intervals[index][0], index);
        std::vector<int> rightIndices(intervals.size(), -1);
        for (size_t index = 0; index < intervals.size(); ++index)
        {
            const auto iterator = leftIndices.lower_bound(intervals[index][1]);
            rightIndices[index] = iterator == leftIndices.cend() ? -1 : static_cast<int>(iterator->second);
        }
        return rightIndices;
    }
};

}

namespace FindRightIntervalTask
{

TEST(FindRightIntervalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({-1}), solution.findRightInterval({{1, 2}}));
    ASSERT_EQ(std::vector<int>({-1, 0, 1}), solution.findRightInterval({{3, 4}, {2, 3}, {1, 2}}));
    ASSERT_EQ(std::vector<int>({-1, 2, -1}), solution.findRightInterval({{1, 4}, {2, 3}, {3, 4}}));
}

}