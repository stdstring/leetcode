#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkIfCanBreak(std::string const &s1, std::string const &s2) const
    {
        const std::array<size_t, AlphabetSize> letterData1(createLetterData(s1));
        const std::array<size_t, AlphabetSize> letterData2(createLetterData(s2));
        size_t size1 = 0;
        size_t size2 = 0;
        int signValue = 0;
        for (size_t letter = 0; letter < AlphabetSize; ++letter)
        {
            const size_t portion1 = letterData1[letter];
            const size_t portion2 = letterData2[letter];
            size1 += portion1;
            size2 += portion2;
            if (signValue == 0)
                signValue = signum(size1, size2);
            else
            {
                if (((signValue < 0) && (size1 > size2)) ||
                    ((signValue > 0) && (size1 < size2)))
                    return false;
            }
        }
        return true;
    }

private:
    constexpr static size_t AlphabetSize = 26;
    constexpr static size_t AlphabetStart = 'a';

    [[nodiscard]] std::array<size_t, AlphabetSize> createLetterData(std::string const &source) const
    {
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        for (const char ch : source)
            ++letterData[ch - AlphabetStart];
        return letterData;
    }

    [[nodiscard]] int signum(size_t size1, size_t size2) const
    {
        return size1 == size2 ? 0 : (size1 < size2 ? -1 : 1);
    }
};

}

namespace CheckIfStringCanBreakAnotherStringTask
{

TEST(CheckIfStringCanBreakAnotherStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.checkIfCanBreak("abc", "xya"));
    ASSERT_EQ(false, solution.checkIfCanBreak("abe", "acd"));
    ASSERT_EQ(true, solution.checkIfCanBreak("leetcodee", "interview"));
}

}