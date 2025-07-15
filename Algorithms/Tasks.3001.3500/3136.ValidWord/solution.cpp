#include <cctype>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isValid(std::string const &word) const
    {
        if (word.size() < 3)
            return false;
        bool hasVowel = false;
        bool hasConsonant = false;
        for (const char ch : word)
        {
            if ((std::isdigit(ch) == 0) && (std::isalpha(ch) == 0))
                return false;
            if (std::isalpha(ch) != 0)
                (isVowel(static_cast<char>(std::tolower(ch))) ? hasVowel : hasConsonant) = true;
        }
        return hasVowel && hasConsonant;
    }

private:
    [[nodiscard]] bool isVowel(char ch) const
    {
        return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u');
    }
};

}

namespace ValidWordTask
{

TEST(ValidWordTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isValid("234Adas"));
    ASSERT_EQ(false, solution.isValid("b3"));
    ASSERT_EQ(false, solution.isValid("a3$e"));
}

}