#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string decodeCiphertext(std::string const &encodedText, int rows) const
    {
        std::string dest;
        const size_t rowCount = rows;
        const size_t columnCount = encodedText.size() / rowCount;
        for (size_t shift = 0; shift < columnCount; ++shift)
        {
            for (size_t row = 0; (row < rowCount) && (row + shift < columnCount); ++row)
            {
                const size_t column = row + shift;
                const size_t index = row * columnCount + column;
                dest.push_back(encodedText[index]);
            }
        }
        while(!dest.empty() && (dest.back() == ' '))
            dest.pop_back();
        return dest;
    }
};

}

namespace DecodeSlantedCiphertextTask
{

TEST(DecodeSlantedCiphertextTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("cipher", solution.decodeCiphertext("ch   ie   pr", 3));
    ASSERT_EQ("i love leetcode", solution.decodeCiphertext("iveo    eed   l te   olc", 4));
    ASSERT_EQ("coding", solution.decodeCiphertext("coding", 1));

}

TEST(DecodeSlantedCiphertextTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(" abc", solution.decodeCiphertext(" b  ac", 2));
}

}