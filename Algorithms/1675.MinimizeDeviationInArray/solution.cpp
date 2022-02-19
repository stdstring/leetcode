#include <algorithm>
#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumDeviation(std::vector<int> const &nums) const
    {
        std::set<int> numbers;
        for (int number : nums)
            numbers.insert(number % 2 == 0 ? number : 2 * number);
        int currentDeviation = getMax(numbers) - getMin(numbers);
        while (getMax(numbers) % 2 == 0)
        {
            int number = getMax(numbers);
            numbers.erase(number);
            numbers.insert(number / 2);
            currentDeviation = std::min(currentDeviation, getMax(numbers) - getMin(numbers));
        }
        return currentDeviation;
    }

private:
    [[nodiscard]] int getMin(std::set<int> const &numbers) const
    {
        return *numbers.cbegin();
    }

    [[nodiscard]] int getMax(std::set<int> const &numbers) const
    {
        return *numbers.crbegin();
    }
};

}

namespace MinimizeDeviationInArrayTask
{

TEST(MinimizeDeviationInArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minimumDeviation({1, 2, 3, 4}));
    ASSERT_EQ(3, solution.minimumDeviation({4, 1, 5, 20, 3}));
    ASSERT_EQ(3, solution.minimumDeviation({2, 10, 8}));
}

TEST(MinimizeDeviationInArrayTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(8360239, solution.minimumDeviation({195643978, 105493962, 103599601, 194267446}));
}

}