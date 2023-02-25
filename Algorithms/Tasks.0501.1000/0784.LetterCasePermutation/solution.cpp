#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> letterCasePermutation(std::string const &s) const
    {
        std::vector<size_t> letters;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (std::isalpha(s[index]))
                letters.push_back(index);
        }
        std::vector<std::string> result;
        for (int mask = 0; mask < (1 << letters.size()); ++mask)
        {
            result.push_back(s);
            for (int letterPos = 0; letterPos < letters.size(); ++letterPos)
            {
                const int letterMask = 1 << letterPos;
                result.back()[letters[letterPos]] = static_cast<char>((mask & letterMask) > 0 ? std::toupper(s[letters[letterPos]]) : std::tolower(s[letters[letterPos]]));
            }
        }
        return result;
    }
};

}

namespace LetterCasePermutationTask
{

TEST(LetterCasePermutationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"a1b2", "A1b2", "a1B2", "A1B2"}), solution.letterCasePermutation("a1b2"));
    ASSERT_EQ(std::vector<std::string>({"3z4", "3Z4"}), solution.letterCasePermutation("3z4"));
    ASSERT_EQ(std::vector<std::string>({"12345"}), solution.letterCasePermutation("12345"));
    ASSERT_EQ(std::vector<std::string>({"0"}), solution.letterCasePermutation("0"));
}

}