#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int> const &candidates, int target) const
    {
        std::vector<int> sortedCandidates(candidates);
        std::sort(sortedCandidates.begin(), sortedCandidates.end());
        std::vector<std::vector<std::vector<int>>> dest(target, std::vector<std::vector<int>>());
        for (size_t index = 0; index < sortedCandidates.size();)
        {
            const int candidate = sortedCandidates[index];
            if (candidate > target)
                break;
            const size_t count = calcCandidateCount(sortedCandidates, index);
            useCandidate(dest, {}, 0, candidate, count, target);
            for (int number = 1; number <= target - candidate; ++number)
            {
                for (std::vector<int> const &combination: dest[number - 1])
                {
                    if (combination.back() != candidate)
                        useCandidate(dest, combination, number, candidate, count, target);
                }
            }
            index += count;
        }
        return dest.back();
    }

private:
    size_t calcCandidateCount(std::vector<int> const &sortedCandidates, size_t index) const
    {
        const int candidate = sortedCandidates[index];
        size_t count = 1;
        for (; index + count < sortedCandidates.size() && sortedCandidates[index + count] == candidate; ++count);
        return count;
    }

    void useCandidate(std::vector<std::vector<std::vector<int>>> &dest, std::vector<int> const &combination, int number, int candidate, size_t count, int target) const
    {
        std::vector<int> currentCombination(combination);
        for (size_t index = 0; index < count && (number + candidate) <= target; ++index, number += candidate)
        {
            currentCombination.push_back(candidate);
            dest[number + candidate - 1].push_back(currentCombination);
        }
    }
};

}

namespace CombinationSumIITask
{

TEST(CombinationSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 5}, {1, 1, 6}, {2, 6}, {1, 7}}), solution.combinationSum2({10, 1, 2, 7, 6, 1, 5}, 8));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 2}, {5}}), solution.combinationSum2({2, 5, 2, 1, 2}, 5));
}

}