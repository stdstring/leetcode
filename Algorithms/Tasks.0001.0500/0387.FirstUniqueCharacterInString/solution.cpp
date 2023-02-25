#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int firstUniqChar(std::string const &s) const
    {
        const int alphabetSize = 26;
        std::array<int, alphabetSize> charPositions{};
        charPositions.fill(0);
        for (size_t index = 0; index < s.size(); ++index)
        {
            const size_t charIndex = s[index] - 'a';
            if (charPositions[charIndex] != -1)
                charPositions[charIndex] = charPositions[charIndex] == 0 ? static_cast<int>(index + 1) : -1;
        }
        int uniqCharIndex = -1;
        for (size_t charIndex = 0; charIndex < alphabetSize; ++charIndex)
        {
            if (charPositions[charIndex] > 0)
                uniqCharIndex = uniqCharIndex == -1 ? charPositions[charIndex] - 1 : std::min(charPositions[charIndex] - 1, uniqCharIndex);
        }
        return uniqCharIndex;
    }
};

}

namespace FirstUniqueCharacterInStringTask
{

TEST(FirstUniqueCharacterInStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(0, solution.firstUniqChar("leetcode"));
    ASSERT_EQ(2, solution.firstUniqChar("loveleetcode"));
}

}