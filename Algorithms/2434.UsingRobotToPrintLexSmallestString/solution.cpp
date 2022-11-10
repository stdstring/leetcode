#include <array>
#include <stack>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string robotWithString(std::string const &s) const
    {
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        for (const char ch : s)
            ++letterData[ch - AlphabetStart];
        std::stack<size_t> robotBuffer;
        std::string dest;
        size_t smallestLetter = 0;
        for (size_t index = 0; index < s.size();)
        {
            size_t currentLetter = s[index] - AlphabetStart;
            smallestLetter = findSmallestLetter(letterData, smallestLetter);
            if (!robotBuffer.empty() && (robotBuffer.top() <= smallestLetter))
            {
                dest.push_back(static_cast<char>(robotBuffer.top() + AlphabetStart));
                robotBuffer.pop();
                continue;
            }
            if (currentLetter == smallestLetter)
                dest.push_back(static_cast<char>(currentLetter + AlphabetStart));
            else
                robotBuffer.push(currentLetter);
            --letterData[currentLetter];
            ++index;
        }
        while (!robotBuffer.empty())
        {
            dest.push_back(static_cast<char>(robotBuffer.top() + AlphabetStart));
            robotBuffer.pop();
        }
        return dest;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    [[nodiscard]] size_t findSmallestLetter(std::array<size_t, AlphabetSize> const &letterData, size_t start) const
    {
        for (size_t index = start; index < AlphabetSize; ++index)
        {
            if (letterData[index] != 0)
                return index;
        }
        return AlphabetSize;
    }
};

}

namespace UsingRobotToPrintLexSmallestStringTask
{

TEST(UsingRobotToPrintLexSmallestStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("azz", solution.robotWithString("zza"));
    ASSERT_EQ("abc", solution.robotWithString("bac"));
    ASSERT_EQ("addb", solution.robotWithString("bdda"));
}

}