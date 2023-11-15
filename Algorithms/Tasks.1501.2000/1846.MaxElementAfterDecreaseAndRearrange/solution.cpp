#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumElementAfterDecrementingAndRearranging(std::vector<int> const &arr) const
    {
        std::vector<int> numbers(arr);
        std::ranges::sort(numbers);
        // skip all 1
        size_t start = 1;
        for (; (start < numbers.size()) && (numbers[start] == 1); ++start){}
        // process all other numbers
        int currentNumber = 1;
        for (size_t index = start; index < numbers.size(); ++index)
        {
            if (currentNumber < numbers[index])
                ++currentNumber;
        }
        return currentNumber;
    }
};

}

namespace MaxElementAfterDecreaseAndRearrangeTask
{

TEST(MaxElementAfterDecreaseAndRearrangeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maximumElementAfterDecrementingAndRearranging({2, 2, 1, 2, 1}));
    ASSERT_EQ(3, solution.maximumElementAfterDecrementingAndRearranging({100, 1, 1000}));
    ASSERT_EQ(5, solution.maximumElementAfterDecrementingAndRearranging({1, 2, 3, 4, 5}));
}

TEST(MaxElementAfterDecreaseAndRearrangeTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumElementAfterDecrementingAndRearranging({73, 98, 9}));
}

}