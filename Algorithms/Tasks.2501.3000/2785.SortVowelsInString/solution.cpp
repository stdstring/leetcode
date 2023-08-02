#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string sortVowels(std::string const &s) const
    {
        std::string result(s);
        std::vector<char> vowels;
        std::vector<size_t> vowelIndices;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (isVowel(s[index]))
            {
                vowels.emplace_back(s[index]);
                vowelIndices.emplace_back(index);
            }
        }
        std::ranges::sort(vowels);
        for (size_t index = 0; index < vowelIndices.size(); ++index)
            result[vowelIndices[index]] = vowels[index];
        return result;
    }

private:
    [[nodiscard]] bool isVowel(char ch) const
    {
        return (ch == 'A') || (ch == 'a') ||
               (ch == 'E') || (ch == 'e') ||
               (ch == 'I') || (ch == 'i') ||
               (ch == 'O') || (ch == 'o') ||
               (ch == 'U') || (ch == 'u');
    }
};

}

namespace SortVowelsInStringTask
{

TEST(SortVowelsInStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("lEOtcede", solution.sortVowels("lEetcOde"));
    ASSERT_EQ("lYmpH", solution.sortVowels("lYmpH"));
}

}