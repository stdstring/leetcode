#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfWeakCharacters(std::vector<std::vector<int>> const &properties) const
    {
        // sort
        std::vector<std::vector<int>> sortedChars(properties);
        std::sort(sortedChars.begin(), sortedChars.end(), [](std::vector<int> const &l, std::vector<int> const &r){return (l[0] < r[0]) || ((l[0] == r[0]) && (l[1] < r[1])); });
        if (sortedChars.front()[0] == sortedChars.back()[0])
            return 0;
        // group by attack
        std::vector<std::pair<size_t, size_t>> groups;
        groups.emplace_back(0, 0);
        for (size_t index = 1; index < sortedChars.size(); ++index)
        {
            if (sortedChars[index][0] == sortedChars[groups.back().first][0])
                groups.back().second = index;
            else
                groups.emplace_back(index, index);
        }
        // calc max group defense stack
        std::stack<int> maxGroupDefenseStack;
        for (auto riterator = groups.crbegin(); riterator != groups.crend(); ++riterator)
            maxGroupDefenseStack.push(std::max(sortedChars[riterator->second][1], maxGroupDefenseStack.empty() ? INT_MIN : maxGroupDefenseStack.top()));
        maxGroupDefenseStack.pop();
        // calc number of weak characters
        size_t result = 0;
        for (size_t groupIndex = 0; !maxGroupDefenseStack.empty(); ++groupIndex)
        {
            if (sortedChars[groups[groupIndex].first][1] < maxGroupDefenseStack.top())
            {
                size_t index = groups[groupIndex].second;
                for (; sortedChars[index][1] >= maxGroupDefenseStack.top(); --index){}
                result += (index - groups[groupIndex].first + 1);
            }
            maxGroupDefenseStack.pop();
        }
        return static_cast<int>(result);
    }
};

}

namespace NumberOfWeakCharactersInGameTask
{

TEST(NumberOfWeakCharactersInGameTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.numberOfWeakCharacters({{5, 5}, {6, 3}, {3, 6}}));
    ASSERT_EQ(1, solution.numberOfWeakCharacters({{2, 2}, {3, 3}}));
    ASSERT_EQ(1, solution.numberOfWeakCharacters({{1, 5}, {10, 4}, {4, 3}}));
}

}