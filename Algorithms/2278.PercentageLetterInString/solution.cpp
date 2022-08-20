#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int percentageLetter(std::string const &s, char letter) const
    {
        return static_cast<int>(100 * std::count(s.cbegin(), s.cend(), letter) / s.size());
    }
};

}

namespace PercentageLetterInStringTask
{

TEST(PercentageLetterInStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(33, solution.percentageLetter("foobar", 'o'));
    ASSERT_EQ(0, solution.percentageLetter("jjjj", 'k'));
}

}
