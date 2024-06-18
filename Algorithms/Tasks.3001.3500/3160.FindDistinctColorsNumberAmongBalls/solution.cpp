#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> queryResults(int _, std::vector<std::vector<int>> const &queries) const
    {
        std::unordered_map<int, int> usedColors;
        std::unordered_map<int, int> ballsColor;
        std::vector<int> result;
        result.reserve(queries.size());
        for (std::vector<int> const &query : queries)
        {
            const int ball = query[0];
            const int color = query[1];
            auto ballIterator = ballsColor.find(ball);
            if (ballIterator != ballsColor.cend())
            {
                const auto colorIterator = usedColors.find(ballIterator->second);
                --colorIterator->second;
                if (colorIterator->second == 0)
                    usedColors.erase(colorIterator);
            }
            else
                ballIterator = ballsColor.emplace(ball, 0).first;
            ballIterator->second = color;
            ++usedColors[color];
            result.emplace_back(static_cast<int>(usedColors.size()));
        }
        return result;
    }
};

}

namespace FindDistinctColorsNumberAmongBallsTask
{

TEST(FindDistinctColorsNumberAmongBallsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 2, 3}), solution.queryResults(4, {{1, 4}, {2, 5}, {1, 3}, {3, 4}}));
    ASSERT_EQ(std::vector<int>({1, 2, 2, 3, 4}), solution.queryResults(4, {{0, 1}, {1, 2}, {2, 2}, {3, 4}, {4, 5}}));
}

}