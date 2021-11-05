#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int canBeTypedWords(std::string const &text, std::string const &brokenLetters) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::array<bool, alphabetSize> brokenLettersData{};
        brokenLettersData.fill(false);
        for (const char brokenLetter : brokenLetters)
            brokenLettersData[brokenLetter - alphabetStart] = true;
        size_t wordsCount = 0;
        size_t canType = true;
        for (const char ch : text)
        {
            if (ch == ' ')
            {
                wordsCount += (canType ? 1 : 0);
                canType = true;
            }
            else if (brokenLettersData[ch - alphabetStart])
                canType = false;
        }
        wordsCount += (canType ? 1 : 0);
        return static_cast<int>(wordsCount);
    }
};

}

namespace MaxNumberOfWordsYouCanTypeTask
{

TEST(MaxNumberOfWordsYouCanTypeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.canBeTypedWords("hello world", "ad"));
    ASSERT_EQ(1, solution.canBeTypedWords("leet code", "lt"));
    ASSERT_EQ(0, solution.canBeTypedWords("leet code", "e"));
}

}