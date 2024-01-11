#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumLength(std::string const &s) const
    {
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<std::vector<size_t>> letterPortions(alphabetSize);
        size_t portionStart = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] != s[portionStart])
            {
                letterPortions[s[portionStart] - alphabetStart].emplace_back(index - portionStart);
                portionStart = index;
            }
        }
        letterPortions[s[portionStart] - alphabetStart].emplace_back(s.size() - portionStart);
        size_t maxLength = 0;
        for (std::vector<size_t> &portions : letterPortions)
        {
            if (portions.empty())
                continue;
            std::ranges::sort(portions, std::greater<int>());
            // from one portion
            if (portions[0] > 2)
                maxLength = std::max(maxLength, portions[0] - 2);
            // from two portions
            if ((portions.size() > 1) && (portions[0] > 1))
                maxLength = std::max(maxLength, std::min(portions[0] - 1, portions[1]));
            // from three portions
            if (portions.size() > 2)
                maxLength = std::max(maxLength, portions[2]);
        }
        return maxLength == 0 ? -1 : static_cast<int>(maxLength);
    }
};

}

namespace FindLongestSpecialSubstrOccursThrice2Task
{

TEST(FindLongestSpecialSubstrOccursThrice2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maximumLength("aaaa"));
    ASSERT_EQ(-1, solution.maximumLength("abcdef"));
    ASSERT_EQ(1, solution.maximumLength("abcaba"));
}

}