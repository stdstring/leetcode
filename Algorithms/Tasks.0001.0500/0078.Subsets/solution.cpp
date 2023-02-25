#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> subsets(std::vector<int> const &nums) const
    {
        const unsigned int subsetsCount = 1u << nums.size();
        std::vector<std::vector<int>> subsets;
        subsets.reserve(subsetsCount);
        subsets.emplace_back();
        for (unsigned int mask = 1; mask < subsetsCount; ++mask)
            subsets.push_back(createSubsetByMask(nums, mask));
        return subsets;
    }

private:
    std::vector<int> createSubsetByMask(std::vector<int> const &nums, unsigned int mask) const
    {
        std::vector<int> subset;
        subset.reserve(nums.size());
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if ((mask & (1u << index)) > 0)
                subset.push_back(nums[index]);
        }
        return subset;
    }
};

}

namespace SubsetsTask
{

TEST(SubsetsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{}, {1}, {2}, {1, 2}, {3}, {1,3}, {2,3}, {1,2,3}}), solution.subsets({1, 2, 3}));
}

}