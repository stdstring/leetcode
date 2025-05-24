#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> findWordsContaining(std::vector<std::string> const &words, char x) const
    {
        std::vector<int> result;
        result.reserve(words.size());
        for (size_t index = 0; index < words.size(); ++index)
        {
            if (words[index].find(x) != std::string::npos)
                result.emplace_back(static_cast<int>(index));
        }
        return result;
    }
};

}

namespace FindWordsContainingCharacterTask
{

TEST(FindWordsContainingCharacterTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1}), solution.findWordsContaining({"leet", "code"}, 'e'));
    ASSERT_EQ(std::vector<int>({0, 2}), solution.findWordsContaining({"abc", "bcd", "aaaa", "cbc"}, 'a'));
    ASSERT_EQ(std::vector<int>(), solution.findWordsContaining({"abc", "bcd", "aaaa", "cbc"}, 'z'));
}

}