#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isSolvable(std::vector<std::string> const &words, std::string const &result) const
    {
        size_t maxWordSize = 0;
        for (std::string const &word : words)
            maxWordSize = std::max(maxWordSize, word.size());
        if ((result.size() < maxWordSize) || (result.size() - maxWordSize > 1))
            return false;
        std::unordered_map<char, int> letterConstraints;
        for (std::string const &word : words)
        {
            for (char ch : word)
                letterConstraints[ch] = 0b1111111111;
        }
        for (char ch : result)
            letterConstraints[ch] = 0b1111111111;
        for (std::string const &word : words)
        {
            if (word.size() > 1)
                letterConstraints[word.front()] = 0b1111111110;
        }
        if (result.size() > 1)
            letterConstraints[result.front()] = 0b1111111110;
        return processDigitPos(words, result, letterConstraints, 0, 0, 0);
    }

private:
    bool canUseDigit(std::unordered_map<char, int> const &letterConstraints, char letter, int digit) const
    {
        return (letterConstraints.at(letter) & (1 << digit)) != 0;
    }

    std::unordered_map<char, int> useDigit(std::unordered_map<char, int> letterConstraints, char letter, int digit) const
    {
        const int digitMask = 1 << digit;
        for (auto &entry : letterConstraints)
            entry.second = entry.first == letter ? digitMask : entry.second & (~digitMask);
        return letterConstraints;
    }

    bool checkConstraints(std::unordered_map<char, int> const &letterConstraints) const
    {
        std::array<int, 10> usedDigits{};
        usedDigits.fill(0);
        for (auto const &entry : letterConstraints)
        {
            if (entry.second == 0)
                return false;
            for (int digit = 0; digit <= 9; ++digit)
            {
                const int mask = 1 << digit;
                if ((entry.second & mask) != 0)
                    usedDigits[digit] = 1;
            }
        }
        size_t unusedCount = 10;
        for (int digit = 0; digit <= 9; ++digit)
        {
            if (usedDigits[digit] == 1)
                --unusedCount;
        }
        return letterConstraints.size() <= (10ul - unusedCount);
    }

    bool processDigitPos(std::vector<std::string> const &words, std::string const &result, std::unordered_map<char, int> const &letterConstraints, size_t digitPos, size_t row, int sum) const
    {
        if (!checkConstraints(letterConstraints))
            return false;
        if (digitPos == result.size())
            return sum == 0;
        if (row == words.size())
        {
            const char letter = result[result.size() - 1 - digitPos];
            return !canUseDigit(letterConstraints, letter, sum % 10) ? false : processDigitPos(words, result, useDigit(letterConstraints, letter, sum % 10), digitPos + 1, 0, sum / 10);
        }
        if (digitPos >= words[row].size())
            return processDigitPos(words, result, letterConstraints, digitPos, row + 1, sum);
        for (int digit = 0; digit <= 9; ++digit)
        {
            const char letter = words[row][words[row].size() - 1 - digitPos];
            if (canUseDigit(letterConstraints, letter, digit) && processDigitPos(words, result, useDigit(letterConstraints, letter, digit), digitPos, row + 1, sum + digit))
                return true;
        }
        return false;
    }
};

}

namespace VerbalArithmeticPuzzleTask
{

TEST(VerbalArithmeticPuzzleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isSolvable({"SEND", "MORE"}, "MONEY"));
    ASSERT_EQ(true, solution.isSolvable({"SIX", "SEVEN", "SEVEN"}, "TWENTY"));
    ASSERT_EQ(true, solution.isSolvable({"THIS", "IS", "TOO"}, "FUNNY"));
    ASSERT_EQ(false, solution.isSolvable({"LEET", "CODE"}, "POINT"));
}

TEST(VerbalArithmeticPuzzleTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isSolvable({"CBA", "CBA", "CBA", "CBA", "CBA"}, "EDD"));
    ASSERT_EQ(true, solution.isSolvable({"A", "B"}, "A"));
}

}