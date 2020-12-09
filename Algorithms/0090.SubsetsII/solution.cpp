#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        std::vector<std::vector<int>> subsets;
        subsets.emplace_back();
        int prevNumber = 0;
        size_t prevCount = 0;
        size_t subsetsSize = subsets.size();
        for (size_t index = 0; index < numbers.size(); ++index)
        {
            int number = numbers[index];
            if (index == 0 || prevNumber != number)
                prevCount = 0;
            for (size_t subsetIndex = 0; subsetIndex < subsetsSize; ++subsetIndex)
            {
                std::vector<int> const &subset = subsets[subsetIndex];
                if (subset.size() < prevCount)
                    continue;
                if (prevCount > 0 && subset[subset.size() - prevCount] != number)
                    continue;
                std::vector<int> newSubset(subset);
                newSubset.push_back(number);
                subsets.push_back(newSubset);
            }
            subsetsSize = subsets.size();
            prevNumber = number;
            ++prevCount;
        }
        return subsets;
    }
};

}

namespace SubsetsIITask
{

TEST(SubsetsIITaskests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{}, {1}, {2}, {1, 2}, {2, 2}, {1, 2, 2}}), solution.subsetsWithDup({1, 2, 2}));
}

TEST(SubsetsIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{}, {1}, {4}, {1, 4}, {4, 4}, {1, 4, 4}, {4, 4, 4}, {1, 4, 4, 4}, {4, 4, 4, 4}, {1, 4, 4, 4, 4}}), solution.subsetsWithDup({4, 4, 4, 1, 4}));
}

}