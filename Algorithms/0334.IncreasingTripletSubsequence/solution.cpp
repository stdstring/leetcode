#include <optional>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool increasingTriplet(std::vector<int> const &nums) const
    {
        int firstNumber = nums[0];
        std::optional<int> secondNumber;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            int number = nums[index];
            if (secondNumber.has_value())
            {
                const int secondValue = secondNumber.value();
                if (secondValue < number)
                    return true;
                if ((firstNumber < number) && (number < secondValue))
                    secondNumber = number;
            }
            if (number < firstNumber)
                firstNumber = number;
            if ((firstNumber < number) && !secondNumber.has_value())
                secondNumber = number;
        }
        return false;
    }
};

}

namespace IncreasingTripletSubsequenceTask
{

TEST(IncreasingTripletSubsequenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.increasingTriplet({1, 2, 3, 4, 5}));
    ASSERT_EQ(false, solution.increasingTriplet({5, 4, 3, 2, 1}));
    ASSERT_EQ(true, solution.increasingTriplet({2, 1, 5, 0, 4, 6}));
}

TEST(IncreasingTripletSubsequenceTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.increasingTriplet({1, 5, 0, 4, 1, 3}));
}

}