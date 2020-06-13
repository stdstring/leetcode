#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string reverseVowels(std::string const &s) const
    {
        std::string result(s);
        int forward = findVowelForward(result, 0);
        int backward = findVowelBackward(result, result.size() - 1);
        while (forward < backward)
        {
            std::swap(result[forward], result[backward]);
            forward = findVowelForward(result, forward + 1);
            backward = findVowelBackward(result, backward - 1);
        }
        return result;
    }

private:
    bool isVowel(char ch) const
    {
        return (ch == 'a') ||
               (ch == 'A') ||
               (ch == 'e') ||
               (ch == 'E') ||
               (ch == 'i') ||
               (ch == 'I') ||
               (ch == 'o') ||
               (ch == 'O') ||
               (ch == 'u') ||
               (ch == 'U');
    }

    int findVowelForward(std::string const &source, int index) const
    {
        while (index < source.size() && !isVowel(source[index]))
            ++index;
        return index;
    }

    int findVowelBackward(std::string const &source, int index) const
    {
        while (index >= 0 && !isVowel(source[index]))
            --index;
        return index;
    }
};

}

namespace ReverseVowelsOfStringTask
{

TEST(ReverseVowelsOfStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("holle", solution.reverseVowels("hello"));
    ASSERT_EQ("leotcede", solution.reverseVowels("leetcode"));
}

TEST(ReverseVowelsOfStringTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("Aa", solution.reverseVowels("aA"));
}

}