#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getSneakyNumbers(std::vector<int> const &nums) const
    {
        std::vector<int> result;
        std::vector<bool> numberUsage(nums.size() - 2, false);
        for (int number : nums)
        {
            if (numberUsage[number])
                result.emplace_back(number);
            numberUsage[number] = true;
        }
        return result;
    }
};

}

namespace TwoSneakyNumbersOfDigitvilleTask
{

TEST(TwoSneakyNumbersOfDigitvilleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 0}), solution.getSneakyNumbers({0, 1, 1, 0}));
    ASSERT_EQ(std::vector<int>({3, 2}), solution.getSneakyNumbers({0, 3, 2, 1, 3, 2}));
    ASSERT_EQ(std::vector<int>({4, 5}), solution.getSneakyNumbers({7, 1, 5, 4, 3, 4, 6, 0, 9, 5, 8, 2}));
}

}