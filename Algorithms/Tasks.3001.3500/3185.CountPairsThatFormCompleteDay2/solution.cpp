#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countCompleteDayPairs(std::vector<int> const &hours) const
    {
        constexpr int hoursCount = 24;
        std::vector<size_t> hoursRests(hoursCount, 0);
        size_t pairsCount = 0;
        for (const int hour : hours)
        {
            const int hourRest = hour % hoursCount;
            const int supplementedRest = (hoursCount - hourRest) % hoursCount;
            pairsCount += hoursRests[supplementedRest];
            ++hoursRests[hourRest];
        }
        return static_cast<long long>(pairsCount);
    }
};

}

namespace CountPairsThatFormCompleteDay2Task
{

TEST(CountPairsThatFormCompleteDay2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countCompleteDayPairs({12, 12, 30, 24, 24}));
    ASSERT_EQ(3, solution.countCompleteDayPairs({72, 48, 24, 3}));
}

}