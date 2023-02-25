#include "gtest/gtest.h"

namespace
{

int guessNumber = 0;

int guess(int n)
{
    if (guessNumber < n)
        return -1;
    if (guessNumber > n)
        return 1;
    return 0;
}

class Solution
{
public:
    int guessNumber(int n) const
    {
        int left = 1;
        int right = n;
        if (guess(left) == 0)
            return left;
        if (guess(right) == 0)
            return right;
        while ((right - left) > 1)
        {
            const int middle = static_cast<int>((static_cast<long long>(right) + static_cast<long long>(left)) / 2);
            switch (guess(middle))
            {
                case 0:
                    return middle;
                case 1:
                    left = middle;
                    break;
                case -1:
                    right = middle;
                    break;
                default:
                    return -1;
            }
        }
        return right;
    }
};

}

namespace GuessNumberHigherOrLowerTask
{

TEST(GuessNumberHigherOrLowerTaskTests, Examples)
{
    const Solution solution;
    guessNumber = 6;
    ASSERT_EQ(guessNumber, solution.guessNumber(10));
}

TEST(GuessNumberHigherOrLowerTaskTests, FromWrongAnswers)
{
    const Solution solution;
    guessNumber = 1702766719;
    ASSERT_EQ(guessNumber, solution.guessNumber(2126753390));
}

}