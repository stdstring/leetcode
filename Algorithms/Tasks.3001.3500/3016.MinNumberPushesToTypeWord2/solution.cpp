#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumPushes(std::string const &word) const
    {
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<size_t> letterData(alphabetSize, 0);
        for (const char ch : word)
            ++letterData[ch - alphabetStart];
        std::ranges::sort(letterData, std::greater<size_t>());
        constexpr size_t availableButtons = 8;
        size_t pushCount = 0;
        for (size_t index = 0; index < alphabetSize; ++index)
            pushCount += (1 + index / availableButtons) * letterData[index];
        return static_cast<int>(pushCount);
    }
};

}

namespace MinNumberPushesToTypeWord2Task
{

TEST(MinNumberPushesToTypeWord2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minimumPushes("abcde"));
    ASSERT_EQ(12, solution.minimumPushes("xyzxyzxyzxyz"));
    ASSERT_EQ(24, solution.minimumPushes("aabbccddeeffgghhiiiiii"));
}

}