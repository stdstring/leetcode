#include <algorithm>
#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> alertNames(std::vector<std::string> const &keyName, std::vector<std::string> const &keyTime) const
    {
        std::map<std::string, std::vector<int>> accessData;
        for (size_t index = 0; index < keyName.size(); ++index)
        {
            auto iterator = accessData.find(keyName[index]);
            if (iterator == accessData.end())
                iterator = accessData.emplace(keyName[index], std::vector<int>()).first;
            iterator->second.push_back(parseTime(keyTime[index]));
        }
        std::vector<std::string> names;
        names.reserve(accessData.size());
        for (auto &entry : accessData)
        {
            std::sort(entry.second.begin(), entry.second.end());
            if (!checkTimeList(entry.second))
                names.push_back(entry.first);
        }
        return names;
    }

private:
    [[nodiscard]] int parseTime(std::string const &time) const
    {
        const int hours = std::stoi(time.substr(0, 2));
        const int minutes = std::stoi(time.substr(3, 2));
        return 60 * hours + minutes;
    }

    [[nodiscard]] bool checkTimeList(std::vector<int> const &timeList) const
    {
        for (size_t index = 1; index < timeList.size() - 1; ++index)
        {
            const int deltaCurrent = timeList[index] - timeList[index - 1];
            const int deltaNext = timeList[index + 1] - timeList[index - 1];
            if ((deltaCurrent <= 60) && (deltaNext <= 60))
                return false;
        }
        return true;
    }
};

}

namespace AlertUsingSameKeyCardTask
{

TEST(AlertUsingSameKeyCardTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"daniel"}), solution.alertNames({"daniel", "daniel", "daniel", "luis", "luis", "luis", "luis"}, {"10:00", "10:40", "11:00", "09:00", "11:00", "13:00", "15:00"}));
    ASSERT_EQ(std::vector<std::string>({"bob"}), solution.alertNames({"alice", "alice", "alice", "bob", "bob", "bob", "bob"}, {"12:01", "12:00", "18:00", "21:00", "21:20", "21:30", "23:00"}));
}

TEST(AlertUsingSameKeyCardTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>(), solution.alertNames({"a", "a", "a", "a", "b", "b", "b", "b", "b", "b", "c", "c", "c", "c"},
                                                              {"01:35", "08:43", "20:49", "00:01", "17:44", "02:50", "18:48", "22:27", "14:12", "18:00", "12:38", "20:40", "03:59", "22:24"}));
}


}