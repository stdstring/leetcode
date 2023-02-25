#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string longestDiverseString(int a, int b, int c) const
    {
        std::string result;
        std::vector<std::pair<char, int>> letterCountData({{'a', a}, {'b', b}, {'c', c}});
        auto sortFun = [](std::pair<char, int> const& left, std::pair<char, int> const& right) { return left.second > right.second; };
        std::sort(letterCountData.begin(), letterCountData.end(), sortFun);
        while (letterCountData[1].second > 0)
        {
            const int firstCount = std::min(result.empty() || result.back() != letterCountData[0].first ? 2 : 1, letterCountData[0].second);
            result.append(firstCount, letterCountData[0].first);
            letterCountData[0].second -= firstCount;
            result.append(1, letterCountData[1].first);
            --letterCountData[1].second;
            std::sort(letterCountData.begin(), letterCountData.end(), sortFun);
        }
        if (letterCountData[0].second > 0)
            result.append(std::min(2, letterCountData[0].second), letterCountData[0].first);
        return result;
    }
};

}

namespace LongestHappyStringTask
{

TEST(LongestHappyStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("ccaccbcc", solution.longestDiverseString(1, 1, 7));
    ASSERT_EQ("aabbc", solution.longestDiverseString(2, 2, 1));
    ASSERT_EQ("aabaa", solution.longestDiverseString(7, 1, 0));
}

TEST(LongestHappyStringTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("aabbcbbcaac", solution.longestDiverseString(4, 4, 3));
    ASSERT_EQ("ccbccbbcba", solution.longestDiverseString(1, 4, 5));
}

}
