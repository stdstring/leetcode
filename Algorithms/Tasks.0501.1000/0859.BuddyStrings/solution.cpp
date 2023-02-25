#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool buddyStrings(std::string const &a, std::string const &b) const
    {
        if (a.size() != b.size())
            return false;
        constexpr size_t alphabetSize = 26;
        std::array<size_t, alphabetSize> letterData{};
        letterData.fill(0);
        std::vector<size_t> unmatchedPositions;
        for (size_t index = 0; index < a.size(); ++index)
        {
            constexpr size_t alphabetStart = 'a';
            ++letterData[a[index] - alphabetStart];
            if (a[index] != b[index])
                unmatchedPositions.push_back(index);
            if (unmatchedPositions.size() > 2)
                return false;
        }
        if (unmatchedPositions.size() == 1)
            return false;
        if (unmatchedPositions.size() == 2)
            return (a[unmatchedPositions[0]] == b[unmatchedPositions[1]]) && (a[unmatchedPositions[1]] == b[unmatchedPositions[0]]);
        return std::any_of(letterData.cbegin(), letterData.cend(), [](size_t letterCount) { return letterCount > 1; });
    }
};

}

namespace BuddyStringsTask
{

TEST(BuddyStringsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.buddyStrings("ab", "ba"));
    ASSERT_EQ(false, solution.buddyStrings("ab", "ab"));
    ASSERT_EQ(true, solution.buddyStrings("aa", "aa"));
}

}