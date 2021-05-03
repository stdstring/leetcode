#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string customSortString(std::string const &s, std::string const &t) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t firstLetter = 'a';
        std::array<size_t, alphabetSize> letterData{};
        letterData.fill(0);
        std::string result;
        for (char ch : t)
            ++letterData[ch - firstLetter];
        for (char ch : s)
        {
            result.append(letterData[ch - firstLetter], ch);
            letterData[ch - firstLetter] = 0;
        }
        for (size_t index = 0; index < alphabetSize; ++index)
        {
            if (letterData[index] > 0)
                result.append(letterData[index], static_cast<char>(firstLetter + index));
        }
        return result;
    }
};

}

namespace CustomSortStringTask
{

TEST(CustomSortStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("cbad", solution.customSortString("cba", "abcd"));
}

}