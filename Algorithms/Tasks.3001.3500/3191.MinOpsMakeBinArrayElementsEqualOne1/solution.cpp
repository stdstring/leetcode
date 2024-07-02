#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        size_t operationCount = 0;
        for (size_t index = 0; index <= numbers.size() - 3; ++index)
        {
            if (numbers[index] == 0)
            {
                ++operationCount;
                numbers[index + 1] = (numbers[index + 1] + 1) % 2;
                numbers[index + 2] = (numbers[index + 2] + 1) % 2;
            }
        }
        for (size_t index = numbers.size() - 2; index < numbers.size(); ++index)
        {
            if (numbers[index] == 0)
                return -1;
        }
        return static_cast<int>(operationCount);
    }
};

}

namespace MinOpsMakeBinArrayElementsEqualOne1Task
{

TEST(MinOpsMakeBinArrayElementsEqualOne1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minOperations({0, 1, 1, 1, 0, 0}));
    ASSERT_EQ(-1, solution.minOperations({0, 1, 1, 1}));
}

}