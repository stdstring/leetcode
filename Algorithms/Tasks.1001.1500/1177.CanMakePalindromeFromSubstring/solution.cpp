#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<bool> canMakePaliQueries(std::string const &s, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<std::vector<size_t>> prefixLetterData(s.size());
        for (size_t index = 0; index < s.size(); ++index)
        {
            prefixLetterData[index] = index > 0 ? prefixLetterData[index - 1] : std::vector<size_t>(AlphabetSize, 0);
            ++prefixLetterData[index][s[index] - AlphabetStart];
        }
        std::vector<bool> answers(queries.size(), false);
        for (size_t index = 0; index < queries.size(); ++index)
            answers[index] = canMakePalindrome(queries[index][0], queries[index][1], queries[index][2], prefixLetterData);
        return answers;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    [[nodiscard]] bool canMakePalindrome(size_t left, size_t right, size_t k, std::vector<std::vector<size_t>> const &prefixLetterData) const
    {
        size_t oddLettersCount = 0;
        for (size_t letter = 0; letter < AlphabetSize; ++letter)
        {
            const size_t currentLetterCount = prefixLetterData[right][letter] - (left > 0 ? prefixLetterData[left - 1][letter] : 0);
            if ((currentLetterCount % 2) == 1)
                ++oddLettersCount;
        }
        if (((right - left + 1) % 2) == 1)
            --oddLettersCount;
        return oddLettersCount <= 2 * k;
    }
};

}

namespace CanMakePalindromeFromSubstringTask
{

TEST(CanMakePalindromeFromSubstringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<bool>({true, false, false, true, true}),
              solution.canMakePaliQueries("abcda", {{3, 3, 0}, {1, 2, 0}, {0, 3, 1}, {0, 3, 2}, {0, 4, 1}}));
    ASSERT_EQ(std::vector<bool>({false, true}),
              solution.canMakePaliQueries("lyb", {{0, 1, 0}, {2, 2, 1}}));
}

}