#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string originalDigits(std::string const &s) const
    {
        std::array<size_t, alphabetSize> lettersData(createLettersData(s));
        std::array<size_t, 10> digitsData{};
        digitsData.fill(0);
        processDigit(lettersData, digitsData, 0, "zero", 'z');
        processDigit(lettersData, digitsData, 2, "two", 'w');
        processDigit(lettersData, digitsData, 6, "six", 'x');
        processDigit(lettersData, digitsData, 4, "four", 'u');
        processDigit(lettersData, digitsData, 5, "five", 'f');
        processDigit(lettersData, digitsData, 7, "seven", 'v');
        processDigit(lettersData, digitsData, 1, "one", 'o');
        processDigit(lettersData, digitsData, 3, "three", 'r');
        processDigit(lettersData, digitsData, 8, "eight", 'g');
        processDigit(lettersData, digitsData, 9, "nine", 'i');
        std::string dest;
        for (size_t digit = 0; digit < 10; ++digit)
            dest.append(digitsData[digit], static_cast<char>('0' + digit));
        return dest;
    }

private:
    static constexpr int alphabetSize = 26;

    std::array<size_t, alphabetSize> createLettersData(std::string const &source) const
    {
        std::array<size_t, alphabetSize> lettersData{};
        lettersData.fill(0);
        for (char letter : source)
            ++lettersData[letter - 'a'];
        return lettersData;
    }

    void processDigit(std::array<size_t, alphabetSize> &lettersData, std::array<size_t, 10> &digitsData, size_t digit, std::string const &digitStr, char keyLetter) const
    {
        const size_t count = lettersData[keyLetter - 'a'];
        digitsData[digit] = count;
        for (char letter : digitStr)
            lettersData[letter - 'a'] -= count;
    }
};

}

namespace ReconstructOriginalDigitsFromEnglishTask
{

TEST(ReconstructOriginalDigitsFromEnglishTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("012", solution.originalDigits("owoztneoer"));
    ASSERT_EQ("45", solution.originalDigits("fviefuro"));
}

TEST(ReconstructOriginalDigitsFromEnglishTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("9", solution.originalDigits("nnei"));
}

}