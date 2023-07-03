#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int punishmentNumber(int n) const
    {
        int result = 0;
        for (int number = 1; number <= n; ++number)
        {
            const int square = number * number;
            if (checkSquare(number, 0, square))
                result += square;
        }
        return result;
    }

private:
    [[nodiscard]] bool checkSquare(int number, int sum, int squareRest) const
    {
        int part = 0;
        int partFactor = 1;
        while (squareRest > 0)
        {
            const int digit = squareRest % 10;
            squareRest /= 10;
            part += (partFactor * digit);
            partFactor *= 10;
            if ((sum + part + squareRest) == number)
                return true;
            if ((sum + part + squareRest) < number)
                continue;
            if (checkSquare(number, sum + part, squareRest))
                return true;
        }
        return false;
    }
};

}

namespace FindPunishmentNumberOfIntegerTask
{

TEST(FindPunishmentNumberOfIntegerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(182, solution.punishmentNumber(10));
    ASSERT_EQ(1478, solution.punishmentNumber(37));
}

}