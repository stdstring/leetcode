#include <algorithm>
#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxNumberOfBalloons(std::string const &text) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::array<size_t, alphabetSize> letterData{};
        letterData.fill(0);
        for (char ch : text)
            ++letterData[ch - alphabetStart];
        // balloon: a - 1, b - 1, l - 2, n - 1, o - 2
        return static_cast<int>(std::min({letterData['a' - alphabetStart],
                                          letterData['b' - alphabetStart],
                                          letterData['l' - alphabetStart] / 2,
                                          letterData['n' - alphabetStart],
                                          letterData['o' - alphabetStart] / 2}));
    }
};

}

namespace MaximumNumberOfBalloonsTask
{

TEST(MaximumNumberOfBalloonsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.maxNumberOfBalloons("nlaebolko"));
    ASSERT_EQ(2, solution.maxNumberOfBalloons("loonbalxballpoon"));
    ASSERT_EQ(0, solution.maxNumberOfBalloons("leetcode"));
}

}