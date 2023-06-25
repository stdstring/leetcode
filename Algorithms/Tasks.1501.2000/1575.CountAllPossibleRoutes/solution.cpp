#include <algorithm>
#include <vector>

#include "gtest/gtest.h"


namespace
{

class Solution
{
public:
    [[nodiscard]] int countRoutes(std::vector<int> const &locations, int start, int finish, int fuel) const
    {
        constexpr int modValue = 1000000007;
        std::vector<std::vector<int>> dp(fuel + 1, std::vector<int>(locations.size(), 0));
        dp[fuel][start] = 1;
        for (int currentFuel = fuel; currentFuel > 0; --currentFuel)
        {
            for (size_t indexFrom = 0; indexFrom < locations.size(); ++indexFrom)
            {
                if (dp[currentFuel][indexFrom] == 0)
                    continue;
                for (size_t indexTo = 0; indexTo < locations.size(); ++indexTo)
                {
                    if (indexFrom == indexTo)
                        continue;
                    const int requiredFuel = std::abs(locations[indexFrom] - locations[indexTo]);
                    if (requiredFuel > currentFuel)
                        continue;
                    const int restFuel = currentFuel - requiredFuel;
                    dp[restFuel][indexTo] = (dp[restFuel][indexTo] + dp[currentFuel][indexFrom]) % modValue;
                }
            }
        }
        int result = 0;
        for (int currentFuel = fuel; currentFuel >= 0; --currentFuel)
            result = (result + dp[currentFuel][finish]) % modValue;
        return result;
    }
};

}

namespace CountAllPossibleRoutesTask
{

TEST(CountAllPossibleRoutesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countRoutes({2, 3, 6, 8, 4}, 1, 3, 5));
    ASSERT_EQ(5, solution.countRoutes({4, 3, 1}, 1, 0, 6));
    ASSERT_EQ(0, solution.countRoutes({5, 2, 1}, 0, 2, 3));
}

}