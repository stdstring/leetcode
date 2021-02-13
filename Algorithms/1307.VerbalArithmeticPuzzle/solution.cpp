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
    bool isSolvable(std::vector<std::string> const& words, std::string const& result) const
    {
        size_t maxWordSize = 0;
        for (std::string const& word : words)
            maxWordSize = std::max(maxWordSize, word.size());
        if ((result.size() < maxWordSize) || (result.size() - maxWordSize > 1))
            return false;
        std::vector<std::string> destWords;
        std::string destResult;
        const int lettersCount = transformInput(words, result, destWords, destResult);
        std::vector<int> letterConstraints(lettersCount, 0);
        for (std::string const& destWord : destWords)
        {
            for (char ch : destWord)
                letterConstraints[ch - FirstChar] = 0b1111111111;
        }
        for (char ch : destResult)
            letterConstraints[ch - FirstChar] = 0b1111111111;
        for (std::string const& destWord : destWords)
        {
            if (destWord.size() > 1)
                letterConstraints[destWord.front() - FirstChar] = 0b1111111110;
        }
        if (destResult.size() > 1)
            letterConstraints[destResult.front() - FirstChar] = 0b1111111110;
        return processDigitPos(destWords, destResult, letterConstraints, 0, 0, 0);
    }

private:
    constexpr static size_t FirstChar = 'A';

    int transformInput(std::vector<std::string> const& sourceWords, std::string const& sourceResult, std::vector<std::string>& destWords, std::string& destResult) const
    {
        std::unordered_map<char, char> letterMap;
        char lettersCount = 0;
        for (std::string const& sourceWord : sourceWords)
        {
            for (char ch : sourceWord)
            {
                if (letterMap.count(ch) == 0)
                    letterMap[ch] = FirstChar + (lettersCount++);
            }
        }
        for (char ch : sourceResult)
        {
            if (letterMap.count(ch) == 0)
                letterMap[ch] = FirstChar + (lettersCount++);
        }
        for (std::string const& sourceWord : sourceWords)
        {
            destWords.emplace_back("");
            for (char ch : sourceWord)
                destWords.back().push_back(letterMap[ch]);
        }
        for (char ch : sourceResult)
            destResult.push_back(letterMap[ch]);
        return static_cast<int>(lettersCount);
    }

    bool canUseDigit(std::vector<int> const &letterConstraints, char letter, int digit) const
    {
        const int mask = 1 << digit;
        return (letterConstraints[letter - FirstChar] & mask) != 0;
    }

    std::vector<int> useDigit(std::vector<int> letterConstraints, char letter, int digit) const
    {
        const int mask = 1 << digit;
        const size_t letterIndex = letter - FirstChar;
        for (size_t index = 0; index < letterConstraints.size(); ++index)
            letterConstraints[index] = index == letterIndex ? mask : letterConstraints[index] & (~mask);
        return letterConstraints;
    }

    bool processDigitPos(std::vector<std::string> const& words, std::string const& result, std::vector<int> const& letterConstraints, size_t digitPos, size_t row, int sum) const
    {
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