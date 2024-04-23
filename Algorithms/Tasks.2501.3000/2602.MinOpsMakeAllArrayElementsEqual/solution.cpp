#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> minOperations(std::vector<int> const &nums, std::vector<int> const &queries) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        std::vector<long long> prefixSums(numbers.size(), 0);
        for (size_t index = 0; index < numbers.size(); ++index)
            prefixSums[index] = (index > 0 ? prefixSums[index - 1] : 0) + numbers[index];
        std::vector<long long> answer(queries.size(), 0);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            const int query = queries[index];
            auto lowerBound = std::ranges::lower_bound(numbers, query);
            if (lowerBound == numbers.cend())
                answer[index] += static_cast<long long>(query * numbers.size() - prefixSums.back());
            else if (lowerBound != numbers.cbegin())
            {
                const size_t lowerBoundIndex = std::distance(numbers.begin(), lowerBound);
                answer[index] += static_cast<long long>(query * lowerBoundIndex - prefixSums[lowerBoundIndex - 1]);
            }
            auto upperBound = std::ranges::upper_bound(numbers, queries[index]);
            if (upperBound != numbers.cend())
            {
                const size_t upperBoundDistance = std::distance(upperBound, numbers.end());
                const size_t upperBoundIndex = numbers.size() - upperBoundDistance;
                answer[index] += static_cast<long long>(prefixSums.back() - (upperBoundIndex > 0 ? prefixSums[upperBoundIndex - 1] : 0) - query * upperBoundDistance);
            }
        }
        return answer;
    }
};

}

namespace MinOpsMakeAllArrayElementsEqualTask
{

TEST(MinOpsMakeAllArrayElementsEqualTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({14, 10}), solution.minOperations({3, 1, 6, 8}, {1, 5}));
    ASSERT_EQ(std::vector<long long>({20}), solution.minOperations({2, 9, 6, 3}, {10}));
}

}