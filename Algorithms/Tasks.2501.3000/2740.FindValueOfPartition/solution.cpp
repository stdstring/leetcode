#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findValueOfPartition(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        int value = numbers.back() - numbers.front();
        for (size_t index = 1; index < numbers.size(); ++index)
            value = std::min(value, numbers[index] - numbers[index - 1]);
        return value;
    }
};

}

namespace FindValueOfPartitionTask
{

TEST(FindValueOfPartitionTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.findValueOfPartition({1, 3, 2, 4}));
    ASSERT_EQ(9, solution.findValueOfPartition({100, 1, 10}));
}

}