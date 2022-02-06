#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> findSubsequences(std::vector<int> const &nums) const
    {
        std::vector<std::vector<int>> subsequences;
        std::vector<int> subsequence;
        createSubsequences(nums, 0, subsequences, subsequence);
        return subsequences;
    }

private:
    void createSubsequences(std::vector<int> const &nums, size_t start, std::vector<std::vector<int>> &subsequences, std::vector<int> &subsequence) const
    {
        std::unordered_set<int> knownNumbers;
        for (size_t index = start; index < nums.size(); ++index)
        {
            if (knownNumbers.count(nums[index]) == 1)
                continue;
            if (!subsequence.empty() && (subsequence.back() > nums[index]))
                continue;
            subsequence.push_back(nums[index]);
            knownNumbers.insert(nums[index]);
            if (subsequence.size() > 1)
                subsequences.push_back(subsequence);
            createSubsequences(nums, index + 1, subsequences, subsequence);
            subsequence.pop_back();
        }
    }
};

}

namespace IncreasingSubsequencesTask
{

TEST(IncreasingSubsequencesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{4, 6}, {4, 6, 7}, {4, 6, 7, 7}, {4, 7}, {4, 7, 7}, {6, 7}, {6, 7, 7}, {7, 7}}), solution.findSubsequences({4, 6, 7, 7}));
    ASSERT_EQ(std::vector<std::vector<int>>({{4, 4}}), solution.findSubsequences({4, 4, 3, 2, 1}));
}

TEST(IncreasingSubsequencesTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2}, {1, 1}, {1, 1, 1}}), solution.findSubsequences({1, 2, 1, 1}));
}

}