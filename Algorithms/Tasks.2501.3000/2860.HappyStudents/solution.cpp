#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countWays(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        int result = (numbers.front() > 0) ? 1 : 0;
        for (size_t index = 1; index < numbers.size(); ++index)
        {
            const int selectedCount = static_cast<int>(index);
            if ((numbers[index - 1] < selectedCount) && (numbers[index] > selectedCount))
                ++result;
        }
        if (numbers.back() < static_cast<int>(numbers.size()))
            ++result;
        return result;
    }
};

}

namespace HappyStudentsTask
{

TEST(HappyStudentsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countWays({1, 1}));
    ASSERT_EQ(3, solution.countWays({6, 0, 3, 3, 6, 7, 2, 7}));
}

}