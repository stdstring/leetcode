#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool closeStrings(std::string const &word1, std::string const &word2) const
    {
        const std::array<size_t, AlphabetSize> letterData1(generateLetterData(word1));
        const std::array<size_t, AlphabetSize> letterData2(generateLetterData(word2));
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if ((letterData1[index] == 0) != (letterData2[index] == 0))
                return false;
        }
        const std::vector<size_t> freq1(generateSortedFrequencies(letterData1));
        const std::vector<size_t> freq2(generateSortedFrequencies(letterData2));
        for (size_t index = 0;  index < freq1.size(); ++index)
        {
            if (freq1[index] != freq2[index])
                return false;
        }
        return true;
    }

private:
    static constexpr size_t AlphabetStart = 'a';
    static constexpr size_t AlphabetSize = 26;

    [[nodiscard]] std::array<size_t, AlphabetSize> generateLetterData(std::string const &word) const
    {
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        for (const char ch : word)
            ++letterData[ch - AlphabetStart];
        return letterData;
    }

    [[nodiscard]] std::vector<size_t> generateSortedFrequencies(std::array<size_t, AlphabetSize> const &letterData) const
    {
        std::vector<size_t> frequencies;
        for (size_t freq : letterData)
        {
            if (freq != 0)
                frequencies.push_back(freq);
        }
        std::sort(frequencies.begin(), frequencies.end());
        return frequencies;
    }
};

}

namespace DetermineIfTwoStringsAreCloseTask
{

TEST(DetermineIfTwoStringsAreCloseTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.closeStrings("abc", "bca"));
    ASSERT_EQ(false, solution.closeStrings("a", "aa"));
    ASSERT_EQ(true, solution.closeStrings("cabbba", "abbccc"));
}

}