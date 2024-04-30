#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long wonderfulSubstrings(std::string const &word) const
    {
        constexpr int alphabetStart = 'a';
        constexpr int alphabetSize = 10;
        constexpr int bitmaskCount = 1 << alphabetSize;
        std::vector<long long> bitmasks(bitmaskCount, 0);
        bitmasks[0] = 1;
        long long result = 0;
        int currentBitmask = 0;
        for (const char currentLetter : word)
        {
            const int currentMask = 1 << (currentLetter - alphabetStart);
            if ((currentBitmask & currentMask) == 0)
                currentBitmask |= currentMask;
            else
                currentBitmask &= ~currentMask;
            result += bitmasks[currentBitmask];
            for (int letter = 0; letter < alphabetSize; ++letter)
            {
                const int changedMask = 1 << letter;
                int changedBitmask = currentBitmask;
                if ((currentBitmask & changedMask) == 0)
                    changedBitmask |= changedMask;
                else
                    changedBitmask &= ~changedMask;
                result += bitmasks[changedBitmask];
            }
            ++bitmasks[currentBitmask];
        }
        return result;
    }
};

}

namespace NumberOfWonderfulSubstringsTask
{

TEST(NumberOfWonderfulSubstringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.wonderfulSubstrings("aba"));
    ASSERT_EQ(9, solution.wonderfulSubstrings("aabb"));
    ASSERT_EQ(2, solution.wonderfulSubstrings("he"));
}

}