#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numOfPairs(std::vector<std::string> const &nums, std::string const &target) const
    {
        size_t pairsCount = 0;
        for (size_t index1 = 0; index1 < nums.size(); ++index1)
        {
            for (size_t index2 = index1 + 1; index2 < nums.size(); ++index2)
            {
                if ((nums[index1].size() + nums[index2].size()) != target.size())
                    continue;
                if ((target.compare(0, nums[index1].size(), nums[index1]) == 0) &&
                    (target.compare(nums[index1].size(), nums[index2].size(), nums[index2]) == 0))
                    ++pairsCount;
                if ((target.compare(0, nums[index2].size(), nums[index2]) == 0) &&
                    (target.compare(nums[index2].size(), nums[index1].size(), nums[index1]) == 0))
                    ++pairsCount;
            }
        }
        return static_cast<int>(pairsCount);
    }
};

}

namespace NumberPairsOfStringsWithConcatEqualTargetTask
{

TEST(NumberPairsOfStringsWithConcatEqualTargetTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.numOfPairs({"777", "7", "77", "77"}, "7777"));
    ASSERT_EQ(2, solution.numOfPairs({"123", "4", "12", "34"}, "1234"));
    ASSERT_EQ(6, solution.numOfPairs({"1", "1", "1"}, "11"));
}

}