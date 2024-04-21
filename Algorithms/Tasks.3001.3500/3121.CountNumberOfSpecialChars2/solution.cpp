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
        constexpr size_t alphabetSize = 26;
        constexpr size_t lowerStart = 'a';
        constexpr size_t upperStart = 'A';
        std::vector<LetterData>letterData(alphabetSize);
        for (size_t index = 0; index < word.size(); ++index)
        {
            const char ch = word[index];
            if ((std::isupper(ch)) && (letterData[ch - upperStart].UpperFirstIndex == std::string::npos))
                letterData[ch - upperStart].UpperFirstIndex = index;
            if (std::islower(ch))
                letterData[ch - lowerStart].LowerLastIndex = index;
        }
        auto predicate = [](LetterData const &data)
        {
            return (data.LowerLastIndex != std::string::npos) &&
                   (data.UpperFirstIndex != std::string::npos) &&
                   (data.LowerLastIndex < data.UpperFirstIndex);
        };
        return static_cast<int>(std::ranges::count_if(letterData, predicate));
    }

private:
    struct LetterData
    {
        size_t LowerLastIndex = std::string::npos;
        size_t UpperFirstIndex = std::string::npos;
    };
};

}

namespace CountNumberOfSpecialChars2Task
{

TEST(CountNumberOfSpecialChars2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numberOfSpecialChars("aaAbcBC"));
    ASSERT_EQ(0, solution.numberOfSpecialChars("abc"));
    ASSERT_EQ(0, solution.numberOfSpecialChars("AbBCab"));
}

}