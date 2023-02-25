#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> majorityElementDirect(std::vector<int> const& nums) const
    {
        std::unordered_map<int, size_t> frequencyMap;
        for (int number : nums)
            frequencyMap[number] += 1;
        std::vector<int> majorityElements;
        const size_t borderValue = nums.size() / 3;
        for (auto const &entry : frequencyMap)
        {
            if (entry.second > borderValue)
                majorityElements.push_back(entry.first);
        }
        return majorityElements;
    }

    std::vector<int> majorityElementBoyerMooreMajorityVote(std::vector<int> const &nums) const
    {
        // from https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
        int candidate1 = INT_MIN;
        int candidate2 = INT_MIN;
        size_t count1 = 0;
        size_t count2 = 0;
        // voting
        for (int number : nums)
        {
            if (number == candidate1)
                ++count1;
            else if (number == candidate2)
                ++count2;
            else if (count1 == 0)
            {
                candidate1 = number;
                ++count1;
            }
            else if (count2 == 0)
            {
                candidate2 = number;
                ++count2;
            }
            else
            {
                --count1;
                --count2;
            }
        }
        // check
        count1 = 0;
        count2 = 0;
        for (int number : nums)
        {
            if (number == candidate1)
                ++count1;
            if (number == candidate2)
                ++count2;
        }
        const size_t borderValue = nums.size() / 3;
        std::vector<int> majorityElements;
        if (count1 > borderValue)
            majorityElements.push_back(candidate1);
        if (count2 > borderValue)
            majorityElements.push_back(candidate2);
        return majorityElements;
    }
};

}

namespace MajorityElementIITask
{

TEST(MajorityElementIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3}), solution.majorityElementDirect({3, 2, 3}));
    ASSERT_EQ(std::vector<int>({3}), solution.majorityElementBoyerMooreMajorityVote({3, 2, 3}));
    ASSERT_EQ(std::vector<int>({1}), solution.majorityElementDirect({1}));
    ASSERT_EQ(std::vector<int>({1}), solution.majorityElementBoyerMooreMajorityVote({1}));
    ASSERT_EQ(std::vector<int>({1, 2}), solution.majorityElementDirect({1, 2}));
    ASSERT_EQ(std::vector<int>({1, 2}), solution.majorityElementBoyerMooreMajorityVote({1, 2}));
}

TEST(MajorityElementIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2}), solution.majorityElementDirect({2, 2}));
    ASSERT_EQ(std::vector<int>({2}), solution.majorityElementBoyerMooreMajorityVote({2, 2}));
}

}