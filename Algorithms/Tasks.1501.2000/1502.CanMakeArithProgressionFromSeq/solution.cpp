#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canMakeArithmeticProgression(std::vector<int> const &arr) const
    {
        if (arr.size() == 2)
            return true;
        std::vector<int> numbers(arr);
        std::sort(numbers.begin(), numbers.end());
        const int delta = numbers[1] - numbers[0];
        for (size_t index = 2; index < numbers.size(); ++index)
        {
            if ((numbers[index] - numbers[index - 1]) != delta)
                return false;
        }
        return true;
    }
};

}

namespace TwoSumTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canMakeArithmeticProgression({3, 5, 1}));
    ASSERT_EQ(false, solution.canMakeArithmeticProgression({1, 2, 4}));
}

}