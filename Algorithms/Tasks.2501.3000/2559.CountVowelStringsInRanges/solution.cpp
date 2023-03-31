#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> vowelStrings(std::vector<std::string> const &words, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<int> prefixSum(words.size(), 0);
        for (size_t index = 0; index < words.size(); ++index)
            prefixSum[index] = (isVowel(words[index].front()) && isVowel(words[index].back()) ? 1 : 0) + (index > 0 ? prefixSum[index - 1] : 0);
        std::vector<int> result(queries.size(), 0);
        for (size_t index = 0; index < queries.size(); ++index)
            result[index] = prefixSum[queries[index][1]] - (queries[index][0] > 0 ? prefixSum[queries[index][0] - 1] : 0);
        return result;
    }

private:
    [[nodiscard]] bool isVowel(char ch) const
    {
        return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u');
    }
};

}

namespace CountVowelStringsInRangesTask
{

TEST(CountVowelStringsInRangesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 3, 0}), solution.vowelStrings({"aba", "bcb", "ece", "aa", "e"}, {{0, 2}, {1, 4}, {1, 1}}));
    ASSERT_EQ(std::vector<int>({3, 2, 1}), solution.vowelStrings({"a", "e", "i"}, {{0, 2}, {0, 1}, {2, 2}}));
}

}