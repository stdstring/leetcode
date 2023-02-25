#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> findRelativeRanks(std::vector<int> const &nums) const
    {
        std::vector<size_t> indices(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
            indices[index] = index;
        std::sort(indices.begin(), indices.end(), [&nums](size_t left, size_t right){ return nums[left] > nums[right]; });
        std::vector<std::string> ranks(indices.size(), "");
        if (indices.size() > 0)
            ranks[indices[0]] = "Gold Medal";
        if (indices.size() > 1)
            ranks[indices[1]] = "Silver Medal";
        if (indices.size() > 2)
            ranks[indices[2]] = "Bronze Medal";
        for (size_t index = 3; index < indices.size(); ++index)
            ranks[indices[index]] = std::to_string(index + 1);
        return ranks;
    }
};

}

namespace RelativeRanksTask
{

TEST(RelativeRanksTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"}), solution.findRelativeRanks({5, 4, 3, 2, 1}));
}

TEST(RelativeRanksTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"}), solution.findRelativeRanks({10, 3, 8, 9, 4}));
}


}