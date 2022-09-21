#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countDaysTogether(std::string const &arriveAlice,
                                        std::string const &leaveAlice,
                                        std::string const &arriveBob,
                                        std::string const &leaveBob) const
    {
        constexpr size_t monthPartStart = 0;
        constexpr size_t monthPartSize = 2;
        constexpr size_t dayPartStart = 3;
        constexpr size_t dayPartSize = 2;
        const std::vector<int> monthDays({31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
        const int arriveAliceMonth = std::stoi(arriveAlice.substr(monthPartStart, monthPartSize));
        const int arriveAliceDay = std::stoi(arriveAlice.substr(dayPartStart, dayPartSize));
        const int leaveAliceMonth = std::stoi(leaveAlice.substr(monthPartStart, monthPartSize));
        const int leaveAliceDay = std::stoi(leaveAlice.substr(dayPartStart, dayPartSize));
        const int arriveBobMonth = std::stoi(arriveBob.substr(monthPartStart, monthPartSize));
        const int arriveBobDay = std::stoi(arriveBob.substr(dayPartStart, dayPartSize));
        const int leaveBobMonth = std::stoi(leaveBob.substr(monthPartStart, monthPartSize));
        const int leaveBobDay = std::stoi(leaveBob.substr(dayPartStart, dayPartSize));
        if ((leaveAliceMonth < arriveBobMonth) || ((leaveAliceMonth == arriveBobMonth) && (leaveAliceDay <  arriveBobDay)))
            return 0;
        if ((leaveBobMonth < arriveAliceMonth) || ((leaveBobMonth == arriveAliceMonth) && (leaveBobDay <  arriveAliceDay)))
            return 0;
        const int arriveMonth = std::max(arriveAliceMonth, arriveBobMonth);
        const int arriveDay = arriveAliceMonth == arriveBobMonth ?
                              std::max(arriveAliceDay, arriveBobDay) :
                              (arriveAliceMonth == arriveMonth ? arriveAliceDay : arriveBobDay);
        const int leaveMonth = std::min(leaveAliceMonth, leaveBobMonth);
        const int leaveDay = leaveAliceMonth == leaveBobMonth ?
                             std::min(leaveAliceDay, leaveBobDay) :
                             (leaveAliceMonth == leaveMonth ? leaveAliceDay : leaveBobDay);
        if (arriveMonth == leaveMonth)
            return leaveDay - arriveDay + 1;
        int totalDays = (monthDays[arriveMonth - 1] - arriveDay + 1) + leaveDay;
        for (int month = arriveMonth + 1; month < leaveMonth; ++month)
            totalDays += monthDays[month - 1];
        return totalDays;
    }
};

}

namespace CountDaysSpentTogetherTask
{

TEST(CountDaysSpentTogetherTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countDaysTogether("08-15", "08-18", "08-16", "08-19"));
    ASSERT_EQ(0, solution.countDaysTogether("10-01", "10-31", "11-01", "12-31"));
}

}