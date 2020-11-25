#include <algorithm>
#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findLUSlength(std::string const &a, std::string const &b) const
    {
        std::array<size_t, alphabetSize> lettersDataA(createLettersData(a));
        std::array<size_t, alphabetSize> lettersDataB(createLettersData(b));
        size_t commonSize = 0;
        size_t uncommonSizeA = 0;
        size_t uncommonSizeB = 0;
        for (size_t index = 0; index < alphabetSize; ++index)
        {
            commonSize += std::min(lettersDataA[index], lettersDataB[index]);
            if (lettersDataA[index] < lettersDataB[index])
                uncommonSizeB += (lettersDataB[index] - lettersDataA[index]);
            if (lettersDataB[index] < lettersDataA[index])
                uncommonSizeA += (lettersDataA[index] - lettersDataB[index]);
        }
        const size_t longestUncommonSize = std::max(uncommonSizeA, uncommonSizeB);
        return longestUncommonSize == 0 ? -1 : static_cast<int>(commonSize + longestUncommonSize);
    }

private:
    static constexpr size_t alphabetSize = 26;

    std::array<size_t, alphabetSize> createLettersData(std::string const &source) const
    {
        std::array<size_t, alphabetSize> lettersData{};
        lettersData.fill(0);
        for (char letter : source)
            ++lettersData[letter - 'a'];
        return lettersData;
    }
};

}

namespace LongestUncommonSubsequenceITask
{

TEST(LongestUncommonSubsequenceITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.findLUSlength("aba", "cdc"));
    ASSERT_EQ(3, solution.findLUSlength("aaa", "bbb"));
    ASSERT_EQ(-1, solution.findLUSlength("aaa", "aaa"));
}

TEST(LongestUncommonSubsequenceITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(17, solution.findLUSlength("aefawfawfawfaw", "aefawfeawfwafwaef"));
}

}