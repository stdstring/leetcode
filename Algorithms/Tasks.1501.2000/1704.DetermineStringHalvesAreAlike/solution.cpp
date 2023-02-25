#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool halvesAreAlike(std::string const &s) const
    {
        std::string vowels("aeiouAEIOU");
        auto isVowel = [&vowels](char ch){ return vowels.find(ch) != std::string::npos; };
        const auto middle = std::next(s.cbegin(), static_cast<int>(s.size() / 2));
        return std::count_if(s.cbegin(), middle, isVowel) ==
               std::count_if(middle, s.cend(), isVowel);
    }
};

}

namespace DetermineStringHalvesAreAlikeTask
{

TEST(DetermineStringHalvesAreAlikeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.halvesAreAlike("book"));
    ASSERT_EQ(false, solution.halvesAreAlike("textbook"));
}

}