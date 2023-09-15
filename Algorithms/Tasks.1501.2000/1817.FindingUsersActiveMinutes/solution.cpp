#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findingUsersActiveMinutes(std::vector<std::vector<int>> const &logs, int k) const
    {
        std::unordered_map<int, std::unordered_set<int>> userActiveMinutesMap;
        for (std::vector<int> const &log : logs)
            userActiveMinutesMap[log[0]].emplace(log[1]);
        std::unordered_map<int, size_t> activeMinutesMap;
        for (auto const& [id, activeMinutesSet] : userActiveMinutesMap)
        {
            int activeMinutes = static_cast<int>(activeMinutesSet.size());
            ++activeMinutesMap[activeMinutes];
        }
        std::vector<int> result(k, 0);
        for (size_t index = 0; index < result.size(); ++index)
        {
            int activeMinutes = static_cast<int>(index + 1);
            auto iterator = activeMinutesMap.find(activeMinutes);
            if (iterator != activeMinutesMap.cend())
                result[index] = static_cast<int>(iterator->second);
        }
        return result;
    }
};

}

namespace FindingUsersActiveMinutesTask
{

TEST(FindingUsersActiveMinutesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 2, 0, 0, 0}),
              solution.findingUsersActiveMinutes({{0, 5}, {1, 2}, {0, 2}, {0, 5}, {1, 3}}, 5));
    ASSERT_EQ(std::vector<int>({1, 1, 0, 0}),
              solution.findingUsersActiveMinutes({{1, 1}, {2, 2}, {2, 3}}, 4));
}

}