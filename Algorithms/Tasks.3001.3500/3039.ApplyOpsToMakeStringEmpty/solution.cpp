#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string lastNonEmptyString(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<LetterData> letterData(alphabetSize);
        size_t maxLetterCount = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            const size_t letterIndex = s[index] - alphabetStart;
            ++letterData[letterIndex].Count;
            letterData[letterIndex].LastIndex = index;
            maxLetterCount = std::max(maxLetterCount, letterData[letterIndex].Count);
        }
        std::string dest;
        dest.reserve(alphabetSize);
        for (size_t letterIndex = 0; letterIndex < alphabetSize; ++letterIndex)
        {
            if (letterData[letterIndex].Count == maxLetterCount)
                dest.push_back(static_cast<char>(alphabetStart + letterIndex));
        }
        auto comp = [&letterData](char l, char r) { return letterData[l - alphabetStart].LastIndex < letterData[r - alphabetStart].LastIndex; };
        std::ranges::sort(dest, comp);
        return dest;
    }

private:
    struct LetterData
    {
        size_t Count = 0;
        size_t LastIndex = std::string::npos;
    };
};

}

namespace ApplyOpsToMakeStringEmptyTask
{

TEST(ApplyOpsToMakeStringEmptyTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("ba", solution.lastNonEmptyString("aabcbbca"));
    ASSERT_EQ("abcd", solution.lastNonEmptyString("abcd"));
}

}