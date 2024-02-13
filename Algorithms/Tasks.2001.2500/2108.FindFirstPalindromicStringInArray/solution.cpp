#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string firstPalindrome(std::vector<std::string> const &words) const
    {
        for (std::string const &word : words)
        {
            if (isPalindrome(word))
                return word;
        }
        return "";
    }

private:
    [[nodiscard]] bool isPalindrome(std::string const &word) const
    {
        for (size_t left = 0, right = word.size() - 1; left < right; ++left, --right)
        {
            if (word[left] != word[right])
                return false;
        }
        return true;
    }
};

}

namespace FindFirstPalindromicStringInArrayTask
{

TEST(FindFirstPalindromicStringInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("ada", solution.firstPalindrome({"abc", "car", "ada", "racecar", "cool"}));
    ASSERT_EQ("racecar", solution.firstPalindrome({"notapalindrome", "racecar"}));
    ASSERT_EQ("", solution.firstPalindrome({"def", "ghi"}));
}

}