#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> const &candidates, int target) const
    {
        std::vector<std::vector<std::vector<int>>> dest(target, std::vector<std::vector<int>>());
        for (int candidate : candidates)
        {
            if (candidate > target)
                continue;
            dest[candidate - 1].push_back({candidate});
            for (int number = 1; number <= target - candidate; ++number)
            {
                for (std::vector<int> const &combination: dest[number - 1])
                {
                    std::vector<int> nextCombination(combination);
                    nextCombination.push_back(candidate);
                    dest[number + candidate - 1].push_back(nextCombination);
                }
            }
        }
        return dest.back();
    }
};

}

namespace CombinationSumTask
{

TEST(CombinationSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{2, 2, 3}, {7}}), solution.combinationSum({2, 3, 6, 7}, 7));
    ASSERT_EQ(std::vector<std::vector<int>>({{2,2,2,2}, {2,3,3}, {3,5}}), solution.combinationSum({2, 3, 5}, 8));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.combinationSum({2}, 1));
    ASSERT_EQ(std::vector<std::vector<int>>({{1}}), solution.combinationSum({1}, 1));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1}}), solution.combinationSum({1}, 2));
}

}