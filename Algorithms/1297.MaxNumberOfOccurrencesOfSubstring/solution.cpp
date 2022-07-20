#include <algorithm>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxFreq(std::string const &s, int maxLetters, int minSize, int maxSize) const
    {
        constexpr char alphabetStart = 'a';
        std::unordered_map<std::string, size_t> frequencies;
        size_t maxCount = 0;
        for (size_t index = 0; index <= s.size() - minSize; ++index)
        {
            std::string substr;
            substr.reserve(maxSize);
            size_t uniqueLetters = 0;
            int substrLetterMask = 0;
            for (size_t shift = 0; (shift < static_cast<size_t>(maxSize)) && (index + shift) < s.size(); ++shift)
            {
                const char ch = s[index + shift];
                const int letterMask = 1 << (ch - alphabetStart);
                if ((substrLetterMask & letterMask) == 0)
                {
                    substrLetterMask |= letterMask;
                    ++uniqueLetters;
                }
                if (uniqueLetters > static_cast<size_t>(maxLetters))
                    break;
                substr.push_back(ch);
                if (substr.size() < static_cast<size_t>(minSize))
                    continue;
                auto iterator = frequencies.find(substr);
                if (iterator == frequencies.end())
                    iterator = frequencies.emplace(substr, 0).first;
                ++iterator->second;
                maxCount = std::max(maxCount, iterator->second);
            }
        }
        return static_cast<int>(maxCount);
    }
};

}

namespace MaxNumberOfOccurrencesOfSubstringTask
{

TEST(MaxNumberOfOccurrencesOfSubstringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxFreq("aababcaab", 2, 3, 4));
    ASSERT_EQ(2, solution.maxFreq("aaaa", 1, 3, 3));
}

}