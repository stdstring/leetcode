#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> shortestToChar(std::string const &s, char c) const
    {
        std::queue<size_t> positions;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] == c)
                positions.push(index);
        }
        positions.push(INT_MAX);
        std::vector<int> shortestDistances(s.size(), 0);
        size_t lastPos = INT_MAX;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (lastPos == INT_MAX)
                shortestDistances[index] = static_cast<int>(positions.front() - index);
            if (index == positions.front())
            {
                lastPos = positions.front();
                positions.pop();
            }
            else
                shortestDistances[index] = static_cast<int>(std::min(lastPos == INT_MAX ? INT_MAX : index - lastPos, positions.front() - index));
        }
        return shortestDistances;
    }
};

}

namespace ShortestDistanceToCharacterTask
{

TEST(ShortestDistanceToCharacterTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0}), solution.shortestToChar("loveleetcode", 'e'));
    ASSERT_EQ(std::vector<int>({3, 2, 1, 0}), solution.shortestToChar("aaab", 'b'));
}

}