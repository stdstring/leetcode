#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfMatchesViaCalc(int n) const
    {
        int matchesCount = 0;
        while (n > 1)
        {
            matchesCount += (n / 2);
            n = (n / 2) + (n % 2);
        }
        return matchesCount;
    }

    [[nodiscard]] int numberOfMatchesViaMath(int n) const
    {
        // There are n teams participating in the tournament.
        // After each match 1 team is eliminated.
        // n - 1 teams needs to be eliminated : hence n - 1 matches.
        return n - 1;
    }
};

}

namespace
{

void checkNumberOfMatches(int expectedResult, int n)
{
    constexpr Solution solution;
    ASSERT_EQ(expectedResult, solution.numberOfMatchesViaCalc(n));
    ASSERT_EQ(expectedResult, solution.numberOfMatchesViaMath(n));
}

}

namespace CountMatchesInTournamentTask
{

TEST(CountMatchesInTournamentTaskTests, Examples)
{
    checkNumberOfMatches(6, 7);
    checkNumberOfMatches(13, 14);
}

}