#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> letterCombinations(std::string const &digits)
    {
        if (digits.empty())
            return {};
        std::vector<std::string> result;
        createLetterCombinations(digits, result, "");
        return result;
    }

private:
    void createLetterCombinations(std::string const &source, std::vector<std::string> &dest, std::string const &prefix)
    {
        const size_t currentIndex = prefix.size();
        const int currentDigit = source[currentIndex] - '0';
        if (mDigitLetters[currentDigit].empty())
            return;
        for (char letter : mDigitLetters[currentDigit])
        {
            std::string current(prefix);
            current.push_back(letter);
            if (currentIndex == (source.size() - 1))
                dest.push_back(current);
            else
                createLetterCombinations(source, dest, current);
        }
    }

    std::string mDigitLetters[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};

}

namespace LetterCombinationsOfPhoneNumberTask
{

TEST(LetterCombinationsOfPhoneNumberTask, Examples)
{
    Solution solution;
    ASSERT_EQ(std::vector<std::string>({"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}), solution.letterCombinations("23"));
}

TEST(LetterCombinationsOfPhoneNumberTask, FromWrongAnswers)
{
    Solution solution;
    ASSERT_EQ(std::vector<std::string>({}), solution.letterCombinations(""));
}

}