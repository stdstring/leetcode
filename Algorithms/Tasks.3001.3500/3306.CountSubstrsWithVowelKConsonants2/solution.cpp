#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countOfSubstrings(std::string const &word, int k) const
    {
        return CountAtLeastK(word, k) - CountAtLeastK(word, k + 1);
    }

private:
    [[nodiscard]] long long CountAtLeastK(std::string const &word, int k) const
    {
        long long result = 0;
        int consonantCount = 0;
        std::unordered_map<char, int> vowels({{'a', 0}, {'e', 0}, {'i', 0}, {'o', 0}, {'u', 0}});
        for (size_t start = 0, end = 0; end < word.size();++end)
        {
            if (isVowel(word[end]))
                ++vowels[word[end]];
            else
                ++consonantCount;
            while ((consonantCount >= k) && IsVowelsEnough(vowels))
            {
                result += static_cast<long long>(word.size() - end);
                if (isVowel(word[start]))
                    --vowels[word[start]];
                else
                    --consonantCount;
                ++start;
            }
        }
        return result;
    }

    [[nodiscard]] bool isVowel(char ch) const
    {
        return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u');
    }

    [[nodiscard]] bool IsVowelsEnough(std::unordered_map<char, int> const &vowels) const
    {
        return (vowels.at('a') > 0) &&
               (vowels.at('e') > 0) &&
               (vowels.at('i') > 0) &&
               (vowels.at('o') > 0) &&
               (vowels.at('u') > 0);
    }
};

}

namespace CountSubstrsWithVowelKConsonants2Task
{

TEST(CountSubstrsWithVowelKConsonants2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.countOfSubstrings("aeioqq", 1));
    ASSERT_EQ(1, solution.countOfSubstrings("aeiou", 0));
    ASSERT_EQ(3, solution.countOfSubstrings("ieaouqqieaouqq", 1));
}

TEST(CountSubstrsWithVowelKConsonants2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countOfSubstrings("iqeaouqi", 2));
    ASSERT_EQ(4, solution.countOfSubstrings("aoaiuefi", 1));
}

}