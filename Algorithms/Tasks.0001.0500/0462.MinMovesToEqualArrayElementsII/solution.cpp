#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMoves2(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        const size_t medianIndex = nums.size() / 2;
        int movesCount = 0;
        for (size_t index = 1; index <= medianIndex; ++index)
        {
            const size_t leftIndex = medianIndex - index;
            movesCount += (numbers[medianIndex] - numbers[leftIndex]);
            const size_t rightIndex = medianIndex + index;
            if (rightIndex < numbers.size())
                movesCount += (numbers[rightIndex] - numbers[medianIndex]);
        }
        return movesCount;
    }
};

}

namespace MinMovesToEqualArrayElementsIITask
{

TEST(MinMovesToEqualArrayElementsIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minMoves2({1, 2, 3}));
    ASSERT_EQ(16, solution.minMoves2({1, 10, 2, 9}));
}

}