#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkIfExist(std::vector<int> const &arr) const
    {
        std::unordered_set<int> numbers;
        for (int number : arr)
        {
            if (numbers.contains(2 * number))
                return true;
            if (((number % 2) == 0) && numbers.contains(number / 2))
                return true;
            numbers.emplace(number);
        }
        return false;
    }
};

}

namespace CheckIfNAndItsDoubleExistTask
{

TEST(CheckIfNAndItsDoubleExistTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkIfExist({10, 2, 5, 3}));
    ASSERT_EQ(false, solution.checkIfExist({3, 1, 7, 11}));
}

TEST(CheckIfNAndItsDoubleExistTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkIfExist({7, 1, 14, 11}));
}

}