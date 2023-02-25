#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSteps(std::string const &s, std::string const &t) const
    {
        const std::array<size_t, AlphabetSize> sourceData(createLetterData(s));
        const std::array<size_t, AlphabetSize> targetData(createLetterData(t));
        size_t stepCount = 0;
        for (size_t index = 0; index < targetData.size(); ++index)
        {
            if (targetData[index] > sourceData[index])
                stepCount += (targetData[index] - sourceData[index]);
        }
        return static_cast<int>(stepCount);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    [[nodiscard]] std::array<size_t, AlphabetSize> createLetterData(std::string const &source) const
    {
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        for (const char ch : source)
            ++letterData[ch - AlphabetStart];
        return letterData;
    }
};

}

namespace MinStepsNumberToMake2StringsAnagramTask
{

TEST(MinStepsNumberToMake2StringsAnagramTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minSteps("bab", "aba"));
    ASSERT_EQ(5, solution.minSteps("leetcode", "practice"));
    ASSERT_EQ(0, solution.minSteps("anagram", "mangaar"));
}

}