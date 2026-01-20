#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> minBitwiseArray(std::vector<int> const &nums) const
    {
        std::vector<int> answer(nums.size());
        for (size_t index = 0; index < nums.size(); ++index)
            answer[index] = constructValue(nums[index]);
        return answer;
    }

private:
    [[nodiscard]] int constructValue(int number) const
    {
        if (number == 2)
            return -1;
        for (int current = 1; current <= number; ++current)
        {
            const int combinationValue = current | (current + 1);
            if (combinationValue == number)
                return current;
        }
        return -1;
    }
};

}

namespace ConstructMinBitwiseArray1Task
{

TEST(ConstructMinBitwiseArray1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({-1, 1, 4, 3}), solution.minBitwiseArray({2, 3, 5, 7}));
    ASSERT_EQ(std::vector<int>({9, 12, 15}), solution.minBitwiseArray({11, 13, 31}));
}

TEST(ConstructMinBitwiseArray1TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({-1, -1, -1}), solution.minBitwiseArray({2, 2, 2}));
}

}