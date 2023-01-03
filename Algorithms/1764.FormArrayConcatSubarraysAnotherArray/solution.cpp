#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canChoose(std::vector<std::vector<int>> const &groups, std::vector<int> const &nums) const
    {
        auto op = [](size_t size, std::vector<int> const &group) { return size + group.size(); };
        size_t groupsRestSize = std::accumulate(groups.cbegin(), groups.cend(), 0ULL, op);
        size_t currentGroup = 0;
        for (size_t index = 0; index < nums.size();)
        {
            if (isMatch(nums, index, groups[currentGroup]))
            {
                index += groups[currentGroup].size();
                groupsRestSize -= groups[currentGroup].size();
                ++currentGroup;
            }
            else
                ++index;
            if (groupsRestSize == 0)
                break;
        }
        return groupsRestSize == 0;
    }

private:
    [[nodiscard]] bool isMatch(std::vector<int> const &nums, size_t start, std::vector<int> const &group) const
    {
        for (size_t index = 0; index < group.size(); ++index)
        {
            if (group[index] != nums[start + index])
                return false;
        }
        return true;
    }
};

}

namespace FormArrayConcatSubarraysAnotherArrayTask
{

TEST(FormArrayConcatSubarraysAnotherArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canChoose({{1, -1, -1}, {3, -2, 0}}, {1, -1, 0, 1, -1, -1, 3, -2, 0}));
    ASSERT_EQ(false, solution.canChoose({{10, -2}, {1, 2, 3, 4}}, {1, 2, 3, 4, 10, -2}));
    ASSERT_EQ(false, solution.canChoose({{1, 2, 3}, {3, 4}},{7, 7, 1, 2, 3, 4, 7, 7}));
}

}