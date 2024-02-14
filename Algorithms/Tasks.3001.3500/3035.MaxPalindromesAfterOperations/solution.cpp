#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxPalindromesAfterOperations(std::vector<std::string> const &words) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<size_t> wordLengths(words.size(), 0);
        std::vector<size_t> letterData(alphabetSize, 0);
        for (size_t index = 0; index < words.size(); ++index)
        {
            wordLengths[index] = words[index].size();
            for (const char ch : words[index])
                ++letterData[ch - alphabetStart];
        }
        size_t pairCount = 0;
        size_t singleCount = 0;
        for (const size_t letterCount : letterData)
        {
            pairCount += letterCount / 2;
            singleCount += ((letterCount % 2) == 0 ? 0 : 1);
        }
        std::ranges::sort(wordLengths);
        size_t palindromeCount = 0;
        for (const size_t wordLength : wordLengths)
        {
            const size_t expectedPairs = wordLength / 2;
            if (pairCount < expectedPairs)
                break;
            pairCount -= expectedPairs;
            if ((wordLength % 2) == 1)
            {
                if (singleCount > 0)
                    --singleCount;
                else if (pairCount > 0)
                {
                    --pairCount;
                    ++singleCount;
                }
                else
                    break;
            }
            ++palindromeCount;
        }
        return static_cast<int>(palindromeCount);
    }
};

}

namespace MaxPalindromesAfterOperationsTask
{

TEST(MaxPalindromesAfterOperationsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxPalindromesAfterOperations({"abbb", "ba", "aa"}));
    ASSERT_EQ(2, solution.maxPalindromesAfterOperations({"abc", "ab"}));
    ASSERT_EQ(1, solution.maxPalindromesAfterOperations({"cd", "ef", "a"}));
}

}