#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countPrefixSuffixPairs(std::vector<std::string> const &words) const
    {
        size_t result = 0;
        for (size_t i = 0; i < words.size(); ++i)
        {
            for (size_t j = i + 1; j < words.size(); ++j)
            {
                if (isPrefixAndSuffix(words[i], words[j]))
                    ++result;
            }
        }
        return static_cast<int>(result);
    }

private:
    [[nodiscard]] bool isPrefixAndSuffix(std::string const &str1, std::string const &str2) const
    {
        return str2.starts_with(str1) && str2.ends_with(str1);
    }
};

}

namespace CountPrefixAndSuffixPairs1Task
{

TEST(CountPrefixAndSuffixPairs1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countPrefixSuffixPairs({"a", "aba", "ababa", "aa"}));
    ASSERT_EQ(2, solution.countPrefixSuffixPairs({"pa", "papa", "ma", "mama"}));
    ASSERT_EQ(0, solution.countPrefixSuffixPairs({"abab", "ab"}));
}

}