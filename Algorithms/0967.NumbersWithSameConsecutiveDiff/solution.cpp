#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> numsSameConsecDiff(int n, int k) const
    {
        std::vector<int> numbers;
        for (int firstDigit = 1; firstDigit <= 9; ++firstDigit)
            fillNumbers(firstDigit, firstDigit, 1, n, k, numbers);
        return numbers;
    }

private:
    void fillNumbers(int head, int lastDigit, size_t currentSize, size_t numberSize, int k, std::vector<int> &numbers) const
    {
        if (currentSize == numberSize)
        {
            numbers.push_back(head);
            return;
        }
        if ((lastDigit >= k) && (k > 0))
            fillNumbers(10 * head + (lastDigit - k), lastDigit - k, currentSize + 1, numberSize, k, numbers);
        if ((lastDigit + k) < 10)
            fillNumbers(10 * head + (lastDigit + k), lastDigit + k, currentSize + 1, numberSize, k, numbers);
    }
};

}

namespace NumbersWithSameConsecutiveDiffTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({181, 292, 707, 818, 929}), solution.numsSameConsecDiff(3, 7));
    ASSERT_EQ(std::vector<int>({10, 12, 21, 23, 32, 34, 43, 45, 54, 56, 65, 67, 76, 78, 87, 89, 98}), solution.numsSameConsecDiff(2, 1));
}

TEST(TwoSumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({11, 22, 33, 44, 55, 66, 77, 88, 99}), solution.numsSameConsecDiff(2, 0));
}

}