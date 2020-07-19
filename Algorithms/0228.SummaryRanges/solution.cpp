#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> summaryRanges(std::vector<int> const& nums) const
    {
        if (nums.empty())
            return {};
        std::vector<std::string> result;
        int lastNumber = nums[0];
        result.push_back(std::to_string(lastNumber));
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if ((lastNumber + 1) == nums[index])
            {
                if (result.back().back() != '>')
                    result.back().append("->");
            }
            else
            {
                if (result.back().back() == '>')
                    result.back().append(std::to_string(lastNumber));
                result.push_back(std::to_string(nums[index]));
            }
            lastNumber = nums[index];
        }
        if (result.back().back() == '>')
            result.back().append(std::to_string(lastNumber));
        return result;
    }
};

}

namespace SummaryRangesTask
{

TEST(SummaryRangesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"0->2", "4->5", "7"}), solution.summaryRanges({0, 1, 2, 4, 5, 7}));
    ASSERT_EQ(std::vector<std::string>({"0", "2->4", "6", "8->9"}), solution.summaryRanges({0, 2, 3, 4, 6, 8, 9}));
}

}