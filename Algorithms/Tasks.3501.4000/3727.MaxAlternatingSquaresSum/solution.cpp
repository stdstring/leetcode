#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxAlternatingSum(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return 1LL * nums[0] * nums[0];
        std::vector<long long> squares(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
            squares[index] = 1LL * nums[index] * nums[index];
        std::ranges::sort(squares);
        long long result = 0;
        for (size_t leftIndex = 0, rightIndex = squares.size() - 1; leftIndex <= rightIndex; ++leftIndex, --rightIndex)
        {
            result += squares[rightIndex];
            if (leftIndex < rightIndex)
                result -= squares[leftIndex];
        }
        return result;
    }
};

}

namespace MaxAlternatingSquaresSumTask
{

TEST(MaxAlternatingSquaresSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.maxAlternatingSum({1, 2, 3}));
    ASSERT_EQ(16, solution.maxAlternatingSum({1, -1, 2, -2, 3, -3}));
}

}