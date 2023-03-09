#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfRounds(std::string const &loginTime, std::string const &logoutTime) const
    {
        constexpr int roundDuration = 15;
        constexpr int dayDuration = 24 * 60;
        int loginMinutes = convertToMinutes(loginTime);
        int logoutMinutes = convertToMinutes(logoutTime);
        if (logoutMinutes < loginMinutes)
            logoutMinutes += dayDuration;
        if ((loginMinutes % roundDuration) > 0)
            loginMinutes += roundDuration - (loginMinutes % roundDuration);
        if ((logoutMinutes % roundDuration) > 0)
            logoutMinutes -= (logoutMinutes % roundDuration);
        return logoutMinutes <= loginMinutes ? 0 : (logoutMinutes - loginMinutes) / roundDuration;
    }

private:
    [[nodiscard]] int convertToMinutes(std::string const &time) const
    {
        constexpr size_t partSize = 2;
        const int hours = std::stoi(time.substr(0, partSize));
        const int minutes = std::stoi(time.substr(partSize + 1));
        return 60 * hours + minutes;
    }
};

}

namespace NumberFullRoundsYouHavePlayedTask
{

TEST(NumberFullRoundsYouHavePlayedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numberOfRounds("09:31", "10:14"));
    ASSERT_EQ(22, solution.numberOfRounds("21:30", "03:00"));
}

}