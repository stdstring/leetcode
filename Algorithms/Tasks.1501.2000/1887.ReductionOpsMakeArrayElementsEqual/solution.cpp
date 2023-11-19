#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int reductionOperations(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers, std::greater<int>());
        if (numbers.front() == numbers.back())
            return 0;
        int operationCount = 0;
        for (size_t index = 0; numbers[index] != numbers.back();)
        {
            const int startValue = numbers[index];
            while (numbers[index] == startValue)
                ++index;
            operationCount += static_cast<int>(index);
        }
        return operationCount;
    }
};

}

namespace ReductionOpsMakeArrayElementsEqualTask
{

TEST(ReductionOpsMakeArrayElementsEqualTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.reductionOperations({5, 1, 3}));
    ASSERT_EQ(0, solution.reductionOperations({1, 1, 1}));
    ASSERT_EQ(4, solution.reductionOperations({1, 1, 2, 2, 3}));
}

}