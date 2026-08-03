#include <algorithm>
#include <optional>
#include <vector>

#include "gtest/gtest.h"


namespace
{

class Solution
{
public:
    [[nodiscard]] std::string stoneGameIIIViaRecursuon(std::vector<int> const &stoneValue) const
    {
        std::vector<std::optional<int>> cache(stoneValue.size());
        const int result = maxResult(stoneValue, 0, cache);
        return getWinner(result);
    }

    [[nodiscard]] std::string stoneGameIIIViaBottomUpDP(std::vector<int> const &stoneValue) const
    {
        constexpr size_t dpSize = 4;
        std::vector<int> dp(dpSize, 0);
        for (size_t index = 0; index < stoneValue.size(); ++index)
        {
            const size_t current = stoneValue.size() - 1 - index;
            dp[current % dpSize] = stoneValue[current] - dp[(current + 1) % dpSize];
            if ((current + 1) < stoneValue.size())
                dp[current % dpSize] = std::max(dp[current % dpSize], stoneValue[current] + stoneValue[current + 1] - dp[(current + 2) % dpSize]);
            if ((current + 2) < stoneValue.size())
                dp[current % dpSize] = std::max(dp[current % dpSize], stoneValue[current] + stoneValue[current + 1] + stoneValue[current + 2] - dp[(current + 3) % dpSize]);
        }
        return getWinner(dp[0]);
    }

private:
    [[nodiscard]] int maxResult(std::vector<int> const &stoneValue, size_t current, std::vector<std::optional<int>> &cache) const
    {
        if (current == stoneValue.size())
            return 0;
        if (cache[current].has_value())
            return cache[current].value_or(0);
        const int oneStoneResult = stoneValue[current] - maxResult(stoneValue, current + 1, cache);
        int twoStoneResult = INT_MIN;
        if ((current + 1) < stoneValue.size())
            twoStoneResult = stoneValue[current] + stoneValue[current + 1] - maxResult(stoneValue, current + 2, cache);
        int threeStoneResult = INT_MIN;
        if ((current + 2) < stoneValue.size())
            threeStoneResult = stoneValue[current] + stoneValue[current + 1] + stoneValue[current + 2] - maxResult(stoneValue, current + 3, cache);
        int result = std::max({oneStoneResult, twoStoneResult, threeStoneResult});
        cache[current] = result;
        return result;
    }

    [[nodiscard]] std::string getWinner(int result) const
    {
        if (result > 0)
            return "Alice";
        if (result < 0)
            return "Bob";
        return "Tie";
    }
};

}

namespace StoneGame3Task
{

TEST(StoneGame3TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("Bob", solution.stoneGameIIIViaRecursuon({1, 2, 3, 7}));
    ASSERT_EQ("Bob", solution.stoneGameIIIViaBottomUpDP({1, 2, 3, 7}));
    ASSERT_EQ("Alice", solution.stoneGameIIIViaRecursuon({1, 2, 3, -9}));
    ASSERT_EQ("Alice", solution.stoneGameIIIViaBottomUpDP({1, 2, 3, -9}));
    ASSERT_EQ("Tie", solution.stoneGameIIIViaRecursuon({1, 2, 3, 6}));
    ASSERT_EQ("Tie", solution.stoneGameIIIViaBottomUpDP({1, 2, 3, 6}));
}

}
