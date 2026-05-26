#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfSpecialChars(std::string const &word) const
    {
        constexpr int hasLower = 1 << 0;
        constexpr int hasUpper = 1 << 1;
        constexpr int specialLetter = hasUpper | hasLower;
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<int> alphabetData(alphabetSize, 0);
        for (const char ch : word)
        {
            alphabetData[std::tolower(ch) - alphabetStart] |= (std::islower(ch) == 0 ? hasUpper : hasLower);
        }
        return static_cast<int>(std::ranges::count_if(alphabetData, [](int letterData) { return letterData == specialLetter; }));
    }
};

}

namespace CountNumberOfSpecialChars2Task
{

TEST(CountNumberOfSpecialChars2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numberOfSpecialChars("aaAbcBC"));
    ASSERT_EQ(0, solution.numberOfSpecialChars("abc"));
    ASSERT_EQ(1, solution.numberOfSpecialChars("abBCab"));
}

}