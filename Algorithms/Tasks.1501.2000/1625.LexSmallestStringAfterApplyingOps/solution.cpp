#include <algorithm>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string findLexSmallestString(std::string const &s, int a, int b) const
    {
        std::string smallestString(s);
        std::unordered_set<std::string> knownStrings;
        std::queue<std::string> processedStrings;
        knownStrings.emplace(s);
        processedStrings.emplace(s);
        while (!processedStrings.empty())
        {
            std::string const &current(processedStrings.front());
            std::string changedString(changeOddChars(current, a));
            std::string rotatedString(rotate(current, b));
            processedStrings.pop();
            if (!knownStrings.contains(changedString))
            {
                knownStrings.emplace(changedString);
                processedStrings.emplace(changedString);
                smallestString = std::min(smallestString, changedString);
            }
            if (!knownStrings.contains(rotatedString))
            {
                knownStrings.emplace(rotatedString);
                processedStrings.emplace(rotatedString);
                smallestString = std::min(smallestString, rotatedString);
            }
        }
        return smallestString;
    }

private:
    [[nodiscard]] std::string changeOddChars(std::string const &source, int a) const
    {
        constexpr int digitStart = '0';
        constexpr int digitCount = 10;
        std::string result(source);
        for (size_t index = 1; index < result.size(); index += 2)
        {
            char nextChar = static_cast<char>(digitStart + (result[index] - digitStart + a) % digitCount);
            result[index] = nextChar;
        }
        return result;
    }

    [[nodiscard]] std::string rotate(std::string const &source, int b) const
    {
        const size_t shift = b;
        std::string result(source);
        for (size_t index = 0; index < source.size(); ++index)
        {
            size_t nextIndex = index < shift ? source.size() - shift + index : index - shift;
            result[nextIndex] = source[index];
        }
        return result;
    }
};

}

namespace LexSmallestStringAfterApplyingOpsTask
{

TEST(LexSmallestStringAfterApplyingOpsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("2050", solution.findLexSmallestString("5525", 9, 2));
    ASSERT_EQ("24", solution.findLexSmallestString("74", 5, 1));
    ASSERT_EQ("0011", solution.findLexSmallestString("0011", 4, 2));
}

}