#include <string>
#include <vector>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string numberToWords(int num)
    {
        if (num == 0)
            return "Zero";
        std::vector<std::string> suffixes = {"", " Thousand", " Million", " Billion"};
        std::string dest;
        for (std::string const &suffix : suffixes)
        {
            if (num == 0)
                break;
            std::string part = translateFrom1To1000(num % 1000);
            if (!part.empty())
                dest = (part + suffix) + (dest.empty() ? "": " ") + dest;
            num /= 1000;
        }
        return dest;
    }

private:
    std::string translateFrom1To100(int num)
    {
        if (num == 0)
            return "";
        if (num < 10)
            return mTranslationFrom1To9[num];
        if (num < 20)
            return mTranslationFrom10To19[num];
        return mTranslationTensFrom20To90[num / 10] + (num % 10 > 0 ? " " + mTranslationFrom1To9[num % 10] : "");
    }

    std::string translateFrom1To1000(int num)
    {
        const int hundreds = num / 100;
        const std::string hundredsDest = hundreds > 0 ? mTranslationFrom1To9[hundreds] + " Hundred" : "";
        const int hundredsRest = num % 100;
        const std::string hundredsRestDest = translateFrom1To100(hundredsRest);
        return hundredsDest + (hundreds > 0 && hundredsRest > 0 ? " " : "") + hundredsRestDest;
    }

    std::unordered_map<int, std::string> mTranslationFrom1To9 = {
        {1, "One"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"},
        {6, "Six"},
        {7, "Seven"},
        {8, "Eight"},
        {9, "Nine"},
    };

    std::unordered_map<int, std::string> mTranslationFrom10To19 = {
        {10, "Ten"},
        {11, "Eleven"},
        {12, "Twelve"},
        {13, "Thirteen"},
        {14, "Fourteen"},
        {15, "Fifteen"},
        {16, "Sixteen"},
        {17, "Seventeen"},
        {18, "Eighteen"},
        {19, "Nineteen"}
    };

    std::unordered_map<int, std::string> mTranslationTensFrom20To90 = {
        {2, "Twenty"},
        {3, "Thirty"},
        {4, "Forty"},
        {5, "Fifty"},
        {6, "Sixty"},
        {7, "Seventy"},
        {8, "Eighty"},
        {9, "Ninety"}
    };
};

}

namespace IntegerToEnglishWordsTask
{

TEST(IntegerToEnglishWordsTaskTests, Examples)
{
    Solution solution;
    ASSERT_EQ("One Hundred Twenty Three", solution.numberToWords(123));
    ASSERT_EQ("Twelve Thousand Three Hundred Forty Five", solution.numberToWords(12345));
    ASSERT_EQ("One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven", solution.numberToWords(1234567));
    ASSERT_EQ("One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One", solution.numberToWords(1234567891));
}

TEST(IntegerToEnglishWordsTaskTests, FromWrongAnswers)
{
    Solution solution;
    ASSERT_EQ("One Thousand", solution.numberToWords(1000));
}

}