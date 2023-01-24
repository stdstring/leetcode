#include <array>
#include <optional>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string greatestLetter(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t uppercaseStart = 'A';
        constexpr size_t lowercaseStart = 'a';
        constexpr int hasUppercaseLetter = 0b01;
        constexpr int hasLowercaseLetter = 0b10;
        constexpr int hasBothLetters = hasUppercaseLetter | hasLowercaseLetter;
        std::array<int, alphabetSize> letterData{};
        letterData.fill(0);
        std::optional<char> bestLetter;
        for (const char ch : s)
        {
            const size_t index = ch - (std::isupper(ch) ? uppercaseStart : lowercaseStart);
            const int mask = std::isupper(ch) ? hasUppercaseLetter : hasLowercaseLetter;
            letterData[index] |= mask;
            if (letterData[index] == hasBothLetters)
            {
                char uppercaseLetter = static_cast<char>(std::toupper(ch));
                if (!bestLetter.has_value() || (bestLetter.value() < uppercaseLetter))
                    bestLetter = uppercaseLetter;
            }
        }
        return bestLetter.has_value() ? std::string(1, bestLetter.value()) : "";
    }
};

}

namespace GreatestEnglishLetterUpperLowerCaseTask
{

TEST(GreatestEnglishLetterUpperLowerCaseTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("E", solution.greatestLetter("lEeTcOdE"));
    ASSERT_EQ("R", solution.greatestLetter("arRAzFif"));
    ASSERT_EQ("", solution.greatestLetter("AbCdEfGhIjK"));
}

}