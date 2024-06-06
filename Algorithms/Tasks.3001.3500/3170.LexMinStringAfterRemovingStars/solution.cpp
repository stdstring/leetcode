#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string clearStars(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<std::vector<size_t>> letters(alphabetSize);
        std::string buffer(s.size(), ' ');
        for (size_t index = 0; index < s.size(); ++index)
        {
            const char current = s[index];
            if (current == '*')
            {
                size_t letter = 0;
                for (; letter < alphabetSize; ++letter)
                {
                    if (!letters[letter].empty())
                        break;
                }
                buffer[letters[letter].back()] = ' ';
                letters[letter].pop_back();
            }
            else
            {
                buffer[index] = current;
                letters[current - alphabetStart].emplace_back(index);
            }
        }
        std::string result;
        result.reserve(s.size());
        std::ranges::copy_if(buffer, std::back_inserter(result), [](char ch) { return ch != ' '; });
        return result;
    }
};

}

namespace LexMinStringAfterRemovingStarsTask
{

TEST(LexMinStringAfterRemovingStarsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("aab", solution.clearStars("aaba*"));
    ASSERT_EQ("abc", solution.clearStars("abc"));
}

}