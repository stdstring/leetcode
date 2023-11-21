#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> findHighAccessEmployees(std::vector<std::vector<std::string>> const &accessTimes) const
    {
        std::unordered_map<std::string, std::vector<int>> employeesMap;
        for (std::vector<std::string> const &accessTime : accessTimes)
        {
            const int hours = 10 * (accessTime[1][0] - '0') + (accessTime[1][1] - '0');
            const int minutes = 10 * (accessTime[1][2] - '0') + (accessTime[1][3] - '0');
            int totalMinutes = 60 * hours + minutes;
            employeesMap[accessTime[0]].emplace_back(totalMinutes);
        }
        std::vector<std::string> highAccessEmployees;
        for (auto &[name, times] : employeesMap)
        {
            std::ranges::sort(times);
            for (size_t index = 2; index < times.size(); ++index)
            {
                if ((times[index] - times[index - 2]) < 60)
                {
                    highAccessEmployees.emplace_back(name);
                    break;
                }
            }
        }
        std::ranges::sort(highAccessEmployees);
        return highAccessEmployees;
    }
};

}

namespace HighAccessEmployeesTask
{

TEST(HighAccessEmployeesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"a"}),
              solution.findHighAccessEmployees({{"a", "0549"}, {"b", "0457"}, {"a", "0532"}, {"a", "0621"}, {"b", "0540"}}));
    ASSERT_EQ(std::vector<std::string>({"c", "d"}),
              solution.findHighAccessEmployees({{"d", "0002"}, {"c", "0808"}, {"c", "0829"}, {"e", "0215"}, {"d", "1508"}, {"d", "1444"}, {"d", "1410"}, {"c", "0809"}}));
    ASSERT_EQ(std::vector<std::string>({"ab", "cd"}),
              solution.findHighAccessEmployees({{"cd", "1025"}, {"ab", "1025"}, {"cd", "1046"}, {"cd", "1055"}, {"ab", "1124"}, {"ab", "1120"}}));
}

}