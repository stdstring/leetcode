#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    char slowestKey(std::vector<int> const &releaseTimes, std::string const &keysPressed) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::array<int, alphabetSize> keyTotalPressed{};
        keyTotalPressed.fill(0);
        int prevReleaseTime = 0;
        size_t bestKey = 0;
        for (size_t index = 0; index < keysPressed.size(); ++index)
        {
            const size_t currentKey = keysPressed[index] - alphabetStart;
            keyTotalPressed[currentKey] = std::max(keyTotalPressed[currentKey], releaseTimes[index] - prevReleaseTime);
            prevReleaseTime = releaseTimes[index];
            if (keyTotalPressed[currentKey] > keyTotalPressed[bestKey] || (keyTotalPressed[currentKey] == keyTotalPressed[bestKey] && currentKey > bestKey))
                bestKey = currentKey;
        }
        return static_cast<char>(alphabetStart + bestKey);
    }
};

}

namespace SlowestKeyTask
{

TEST(SlowestKeyTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ('c', solution.slowestKey({9, 29, 49, 50}, "cbcd"));
    ASSERT_EQ('a', solution.slowestKey({12, 23, 36, 46, 62}, "spuda"));
}

}