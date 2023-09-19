#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSteps(std::string const &s, std::string const &t) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<size_t> sLetterData(alphabetSize, 0);
        for (const char ch : s)
            ++sLetterData[ch - alphabetStart];
        std::vector<size_t> tLetterData(alphabetSize, 0);
        for (const char ch : t)
            ++tLetterData[ch - alphabetStart];
        size_t result = 0;
        for (size_t index = 0; index < alphabetSize; ++index)
            result += (std::max(sLetterData[index], tLetterData[index]) - std::min(sLetterData[index], tLetterData[index]));
        return static_cast<int>(result);
    }
};

}

namespace MinNumberStepsMake2StringsAnagramIITask
{

TEST(MinNumberStepsMake2StringsAnagramIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.minSteps("leetcode", "coats"));
    ASSERT_EQ(0, solution.minSteps("night", "thing"));
}

}