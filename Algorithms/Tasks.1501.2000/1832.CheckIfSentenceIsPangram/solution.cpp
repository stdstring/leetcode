#include <algorithm>
#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkIfPangram(std::string const &sentence) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::array<bool, alphabetSize> letters{};
        letters.fill(false);
        for (const char ch : sentence)
            letters[ch - alphabetStart] = true;
        return std::all_of(letters.cbegin(), letters.cend(), [](bool value){ return value; });
    }
};

}

namespace CheckIfSentenceIsPangramTask
{

TEST(CheckIfSentenceIsPangramTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkIfPangram("thequickbrownfoxjumpsoverthelazydog"));
    ASSERT_EQ(false, solution.checkIfPangram("leetcode"));
}

}
