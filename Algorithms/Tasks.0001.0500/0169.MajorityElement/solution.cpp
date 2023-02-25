#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int majorityElement(std::vector<int> const &nums) const
    {
        std::unordered_map<int, size_t> numsCountData;
        for (int num : nums)
        {
            std::unordered_map<int, size_t>::iterator entry = numsCountData.find(num);
            if (entry == numsCountData.end())
                numsCountData.emplace(num, 1);
            else
                ++(entry->second);
        }
        int majorityElement = 0;
        size_t majorityElementCount = 0;
        for (std::unordered_map<int, size_t>::value_type const &entry : numsCountData)
        {
            if (entry.second > majorityElementCount)
            {
                majorityElement = entry.first;
                majorityElementCount = entry.second;
            }
        }
        return majorityElement;
    }
};

}

namespace MajorityElementTask
{

TEST(MajorityElementTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.majorityElement({3, 2, 3}));
    ASSERT_EQ(2, solution.majorityElement({2, 2, 1, 1, 1, 2, 2}));
}

TEST(MajorityElementTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(5, solution.majorityElement({6, 5, 5}));
}

}