#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int beautySum(std::string const &s) const
    {
        std::vector<std::vector<size_t>> letterData(s.size(), std::vector<size_t>(AlphabetSize, 0));
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (index > 0)
                letterData[index] = letterData[index - 1];
            ++letterData[index][s[index] - AlphabetStart];
        }
        size_t result = 0;
        for (size_t fromIndex = 0; fromIndex < s.size(); ++fromIndex)
        {
            for (size_t toIndex = fromIndex; toIndex < s.size(); ++toIndex)
                result += calcBeauty(letterData, fromIndex, toIndex);
        }
        return static_cast<int>(result);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    size_t calcBeauty(std::vector<std::vector<size_t>> const &letterData, size_t fromIndex, size_t toIndex) const
    {
        size_t minFreq = INT_MAX;
        size_t maxFreq = 0;
        for (size_t ch = 0; ch < AlphabetSize; ++ch)
        {
            if (letterData[toIndex][ch] == (fromIndex > 0 ? letterData[fromIndex - 1][ch] : 0))
                continue;
            const size_t currentFreq = letterData[toIndex][ch] - (fromIndex > 0 ? letterData[fromIndex - 1][ch] : 0);
            minFreq = std::min(minFreq, currentFreq);
            maxFreq = std::max(maxFreq, currentFreq);
        }
        return maxFreq - minFreq;
    }
};

}

namespace SumOfBeautyAllSubstringsTask
{

TEST(SumOfBeautyAllSubstringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.beautySum("aabcb"));
    ASSERT_EQ(17, solution.beautySum("aabcbaa"));
}

}