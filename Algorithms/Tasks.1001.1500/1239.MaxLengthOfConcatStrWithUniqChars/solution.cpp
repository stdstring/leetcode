#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxLength(std::vector<std::string> const &arr) const
    {
        std::vector<uint32_t> wordUsedLetters;
        std::transform(arr.cbegin(), arr.cend(), std::back_inserter(wordUsedLetters), [this](std::string const &word){ return createUsedLettersData(word); });
        const uint32_t maxCombinationValue = 1 << arr.size();
        size_t maxPossibleLength = 0;
        for (uint32_t combination = 1; combination < maxCombinationValue; ++combination)
        {
            uint32_t usedLetters = 0;
            size_t currentLength = 0;
            for (size_t wordIndex = 0; wordIndex < arr.size(); ++wordIndex)
            {
                if ((combination & (1 << wordIndex)) == 0)
                    continue;
                if (wordUsedLetters[wordIndex] == 0 || (usedLetters & wordUsedLetters[wordIndex]) > 0)
                {
                    currentLength = 0;
                    break;
                }
                usedLetters |= wordUsedLetters[wordIndex];
                currentLength += arr[wordIndex].size();
            }
            maxPossibleLength = std::max(maxPossibleLength, currentLength);
        }
        return static_cast<int>(maxPossibleLength);
    }

private:
    static constexpr uint32_t AlphabetStart = 'a';

    uint32_t createUsedLettersData(std::string const &word) const
    {
        uint32_t usedLettersData = 0;
        for (char ch : word)
        {
            const uint32_t letter = 1 << (ch - AlphabetStart);
            if ((usedLettersData & letter) > 0)
                return 0;
            usedLettersData |= letter;
        }
        return usedLettersData;
    }
};

}

namespace MaxLengthOfConcatStrWithUniqCharsTask
{

TEST(MaxLengthOfConcatStrWithUniqCharsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.maxLength({"un", "iq", "ue"}));
    ASSERT_EQ(6, solution.maxLength({"cha", "r", "act", "ers"}));
    ASSERT_EQ(26, solution.maxLength({"abcdefghijklmnopqrstuvwxyz"}));
}

}