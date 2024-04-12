#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minOperationsToMakeMedianK(std::vector<int> const &nums, int k) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        const size_t medianRight = numbers.size() / 2;
        if (numbers[medianRight] == k)
            return 0;
        long long operationCount = 0;
        if (numbers[medianRight] < k)
        {
            operationCount += (k - numbers[medianRight]);
            for (size_t index = medianRight + 1; (index < numbers.size()) && (numbers[index] < k); ++index)
                operationCount += (k - numbers[index]);
        }
        else
        {
            operationCount += (numbers[medianRight] - k);
            for (size_t rIndex = numbers.size() - 1 - medianRight + 1; (rIndex < numbers.size()) && (numbers[numbers.size() - 1 - rIndex] > k); ++rIndex)
                operationCount += (numbers[numbers.size() - 1 - rIndex] - k);
        }
        return operationCount;
    }
};

}

namespace MinOpsMakeMedianOfArrayEqualKTask
{

TEST(MinOpsMakeMedianOfArrayEqualKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperationsToMakeMedianK({2, 5, 6, 8, 5}, 4));
    ASSERT_EQ(3, solution.minOperationsToMakeMedianK({2, 5, 6, 8, 5}, 7));
    ASSERT_EQ(0, solution.minOperationsToMakeMedianK({1, 2, 3, 4, 5, 6}, 4));
}

}