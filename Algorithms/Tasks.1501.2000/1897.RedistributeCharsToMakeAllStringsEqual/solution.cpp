#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool makeEqual(std::vector<std::string> const &words) const
    {
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<size_t> letters(alphabetSize, 0);
        for (std::string const &word : words)
        {
            for (const char ch : word)
                ++letters[ch - alphabetStart];
        }
        return std::ranges::all_of(letters, [&words](size_t letterCount) { return (letterCount % words.size()) == 0; });
    }
};

}

namespace RedistributeCharsToMakeAllStringsEqualTask
{

TEST(RedistributeCharsToMakeAllStringsEqualTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.makeEqual({"abc", "aabc", "bc"}));
    ASSERT_EQ(false, solution.makeEqual({"ab", "a"}));
}

}