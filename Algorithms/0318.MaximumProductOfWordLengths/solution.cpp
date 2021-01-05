#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxProduct(std::vector<std::string> const &words) const
    {
        std::vector<size_t> wordsLetterUsage;
        wordsLetterUsage.reserve(words.size());
        for (std::string const &word : words)
            wordsLetterUsage.push_back(calcLetterUsage(word));
        size_t maxProduct = 0;
        for (size_t i = 0; i < words.size(); ++i)
        {
            for (size_t j = i + 1; j < words.size(); ++j)
            {
                if ((wordsLetterUsage[i] & wordsLetterUsage[j]) == 0)
                    maxProduct = std::max(maxProduct, words[i].size() * words[j].size());
            }
        }
        return static_cast<int>(maxProduct);
    }

private:
    size_t calcLetterUsage(std::string const &word) const
    {
        size_t result = 0;
        for (char ch : word)
            result |= 1ull << (ch - 'a');
        return result;
    }
};

}

namespace MaximumProductOfWordLengthsTask
{

TEST(MaximumProductOfWordLengthsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(16, solution.maxProduct({"abcw", "baz", "foo", "bar", "xtfn", "abcdef"}));
    ASSERT_EQ(4, solution.maxProduct({"a", "ab", "abc", "d", "cd", "bcd", "abcd"}));
    ASSERT_EQ(0, solution.maxProduct({"a", "aa", "aaa", "aaaa"}));
}

}