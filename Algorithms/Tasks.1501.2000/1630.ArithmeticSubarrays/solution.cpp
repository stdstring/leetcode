#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<bool> checkArithmeticSubarrays(std::vector<int> const &nums, std::vector<int> const &l, std::vector<int> const &r) const
    {
        std::vector<bool> result(l.size(), false);
        for (size_t index = 0; index < l.size(); ++index)
            result[index] = checkArithmeticSubarray(nums, l[index], r[index]);
        return result;
    }

private:
    bool checkArithmeticSubarray(std::vector<int> const &nums, int left, int right) const
    {
        if ((right - left) < 2)
            return true;
        std::vector<int> portion(std::next(nums.cbegin(), left), std::next(nums.cbegin(), right + 1));
        std::ranges::sort(portion);
        const int delta = portion[1] - portion[0];
        for (size_t index = 2; index < portion.size(); ++index)
        {
            if ((portion[index] - portion[index - 1]) != delta)
                return false;
        }
        return true;
    }
};

}

namespace ArithmeticSubarraysTask
{

TEST(ArithmeticSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<bool>({true, false, true}),
              solution.checkArithmeticSubarrays({4, 6, 5, 9, 3, 7}, {0, 0, 2}, {2, 3, 5}));
    ASSERT_EQ(std::vector<bool>({false, true, false, false, true, true}),
              solution.checkArithmeticSubarrays({-12, -9, -3, -12, -6, 15, 20, -25, -20, -15, -10}, {0, 1, 6, 4, 8, 7}, {4, 4, 9, 7, 9, 10}));
}

}