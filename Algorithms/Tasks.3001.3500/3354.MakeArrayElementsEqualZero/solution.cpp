#include <cmath>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countValidSelections(std::vector<int> const &nums) const
    {
        int suffixSum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        int prefixSum = 0;
        size_t validSelections = 0;
        for (int number : nums)
        {
            prefixSum += number;
            suffixSum -= number;
            if (number == 0)
            {
                int delta = std::abs(prefixSum - suffixSum);
                if (delta == 0)
                    validSelections += 2;
                if (delta == 1)
                    ++validSelections;
            }
            if ((prefixSum - suffixSum) > 1)
                break;
        }
        return static_cast<int>(validSelections);
    }
};

}

namespace MakeArrayElementsEqualZeroTask
{

TEST(MakeArrayElementsEqualZeroTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countValidSelections({1, 0, 2, 0, 3}));
    ASSERT_EQ(0, solution.countValidSelections({2, 3, 4, 0, 4, 1, 0}));
}

}