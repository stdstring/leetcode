#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countVowels(std::string const &word) const
    {
        size_t result = 0;
        for (size_t index = 0; index < word.size(); ++index)
        {
            if (isVowel(word[index]))
                result += (index + 1) * (word.size() - index);
        }
        return static_cast<long long>(result);
    }

private:
    [[nodiscard]] bool isVowel(char ch) const
    {
        return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u');
    }
};

}

namespace VowelsOfAllSubstringsTask
{

TEST(VowelsOfAllSubstringsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.countVowels("aba"));
    ASSERT_EQ(3, solution.countVowels("abc"));
    ASSERT_EQ(0, solution.countVowels("ltcd"));
}

}