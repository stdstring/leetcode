#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxVowels(std::string const &s, int k) const
    {
        const size_t substringSize = k;
        size_t currentVowels = 0;
        for (size_t index = 0; index < substringSize; ++index)
        {
            if (isVowel(s[index]))
                ++currentVowels;
        }
        size_t maxVowels = currentVowels;
        for (size_t index = substringSize; index < s.size(); ++index)
        {
            if (isVowel(s[index - substringSize]))
                --currentVowels;
            if (isVowel(s[index]))
                ++currentVowels;
            maxVowels = std::max(maxVowels, currentVowels);
        }
        return static_cast<int>(maxVowels);
    }

private:
    [[nodiscard]] bool isVowel(char ch) const
    {
        return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u');
    }
};

}

namespace MaxNumberOfVowelsInSubstrOfGivenLengthTask
{

TEST(MaxNumberOfVowelsInSubstrOfGivenLengthTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.maxVowels("abciiidef", 3));
    ASSERT_EQ(2, solution.maxVowels("aeiou", 2));
    ASSERT_EQ(2, solution.maxVowels("leetcode", 3));
}

}