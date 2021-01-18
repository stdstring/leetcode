#include <cstdint>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> findErrorNums(std::vector<int> const &nums) const
    {
        std::vector<uint8_t> numbers(nums.size(), 0);
        int duplicateNumber = 0;
        for (int number : nums)
        {
            const size_t index = static_cast<size_t>(number) - 1;
            if (numbers[index]  == 0)
                numbers[index] = 1;
            else
                duplicateNumber = number;
        }
        int missingNumber = 0;
        for (size_t index = 0; index < numbers.size(); ++index)
        {
            if (numbers[index] == 0)
            {
                missingNumber = static_cast<int>(index + 1);
                break;
            }
        }
        return {duplicateNumber, missingNumber};
    }
};

}

namespace SetMismatchTask
{

TEST(SetMismatchTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, 3}), solution.findErrorNums({1, 2, 2, 4}));
    ASSERT_EQ(std::vector<int>({1, 2}), solution.findErrorNums({1, 1}));
}

TEST(SetMismatchTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, 1}), solution.findErrorNums({2, 2}));
}

}