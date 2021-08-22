#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string reorganizeString(std::string const &source) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::array<size_t, alphabetSize + 1> charData{};
        charData.fill(0);
        for (char ch : source)
            ++charData[ch - alphabetStart];
        std::string result;
        size_t lastChar = alphabetSize;
        for (size_t index = 0; index < source.size(); ++index)
        {
            size_t bestChar = alphabetSize;
            for (size_t currentChar = 0; currentChar < alphabetSize; ++currentChar)
            {
                if (currentChar != lastChar && (charData[currentChar] > 0) && (charData[currentChar] > charData[bestChar]))
                    bestChar = currentChar;
            }
            if (bestChar == alphabetSize)
                return "";
            result.push_back(static_cast<char>(bestChar + alphabetStart));
            --charData[bestChar];
            lastChar = bestChar;
        }
        return result;
    }
};

}

namespace ReorganizeStringTask
{

TEST(ReorganizeStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("aba", solution.reorganizeString("aab"));
    ASSERT_EQ("", solution.reorganizeString("aaab"));
}

}
