#include <algorithm>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxFreqSum(std::string const &s) const
    {
        std::unordered_map<char, size_t> vowelFrequencies;
        std::unordered_map<char, size_t> consonantFrequencies;
        for (char ch : s)
        {
            ++(isVowel(ch) ? vowelFrequencies : consonantFrequencies)[ch];
        }
        size_t maxVowelFrequency = 0;
        size_t maxConsonantFrequency = 0;
        for (auto const &[_, frequency] : vowelFrequencies)
            maxVowelFrequency = std::max(frequency, maxVowelFrequency);
        for (auto const &[_, frequency] : consonantFrequencies)
            maxConsonantFrequency = std::max(frequency, maxConsonantFrequency);
        return static_cast<int>(maxVowelFrequency + maxConsonantFrequency);
    }

private:
    [[nodiscard]] bool isVowel(char ch) const
    {
        return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u');
    }
};

}

namespace FindMostFrequentVowelConsonantTask
{

TEST(FindMostFrequentVowelConsonantTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.maxFreqSum("successes"));
    ASSERT_EQ(3, solution.maxFreqSum("aeiaeia"));
}

}