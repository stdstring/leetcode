#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> answerQueries(std::vector<int> const &nums, std::vector<int> const &queries) const
    {
        std::vector<int> sortedNumbers(nums);
        std::sort(sortedNumbers.begin(), sortedNumbers.end());
        std::vector<int> prefixSum(sortedNumbers.size(), 0);
        for (size_t index = 0; index < sortedNumbers.size(); ++index)
            prefixSum[index] = sortedNumbers[index] + (index > 0 ? prefixSum[index - 1] : 0);
        std::vector<int> answers(queries.size(), 0);
        for (size_t index = 0; index < queries.size(); ++index)
            answers[index] = static_cast<int>(calcSubsequenceSize(prefixSum, queries[index]));
        return answers;
    }

private:
    [[nodiscard]] size_t calcSubsequenceSize(std::vector<int> const &prefixSum, int value) const
    {
        if (value < prefixSum.front())
            return 0;
        if (value == prefixSum.front())
            return 1;
        if (value >= prefixSum.back())
            return prefixSum.size();
        size_t left = 0;
        size_t right = prefixSum.size() - 1;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            if (prefixSum[middle] == value)
                return middle + 1;
            if (prefixSum[middle] < value)
                left = middle;
            if (prefixSum[middle] > value)
                right = middle;
        }
        return left + 1;
    }
};

}

namespace LongestSubseqWithLimitedSumTask
{

TEST(LongestSubseqWithLimitedSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 3, 4}), solution.answerQueries({4, 5, 2, 1}, {3, 10, 21}));
    ASSERT_EQ(std::vector<int>({0}), solution.answerQueries({2, 3, 4, 5}, {1}));
}

}