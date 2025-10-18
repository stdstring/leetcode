#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDistinctElements(std::vector<int> const &nums, int k) const
    {
        std::map<int, size_t> numbers;
        for (int number : nums)
            ++numbers[number];
        int lastUsedNumber = INT_MIN;
        size_t result = 0;
        for (auto const &[number, count] : numbers)
        {
            for (size_t index = 0; (index < count) && (number + k) > lastUsedNumber; ++index)
            {
                ++result;
                lastUsedNumber = (lastUsedNumber < (number - k) ? (number - k) : lastUsedNumber + 1);
            }
        }
        return static_cast<int>(result);
    }
};

}

namespace MaxNumberDistinctElementsAfterOpsTask
{

TEST(MaxNumberDistinctElementsAfterOpsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.maxDistinctElements({1, 2, 2, 3, 3, 4}, 2));
    ASSERT_EQ(3, solution.maxDistinctElements({4, 4, 4, 4}, 1));
}

}