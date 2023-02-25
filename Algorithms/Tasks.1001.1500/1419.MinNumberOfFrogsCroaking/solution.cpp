#include <algorithm>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minNumberOfFrogs(std::string const &croakOfFrogs) const
    {
        size_t numberOfFrogs = 0;
        size_t currentNumberOfFrogs = 0;
        const std::unordered_map<char, char> transitions({{'c', 0}, {'r', 'c'}, {'o', 'r'}, {'a', 'o'}, {'k', 'a'}});
        constexpr char startChar = 'c';
        constexpr char lastChar = 'k';
        std::unordered_map<char, size_t> letters;
        for (char ch : croakOfFrogs)
        {
            if (ch == startChar)
            {
                ++currentNumberOfFrogs;
                numberOfFrogs = std::max(numberOfFrogs, currentNumberOfFrogs);
            }
            char prevChar = transitions.at(ch);
            if (prevChar != 0)
            {
                if (letters[prevChar] == 0)
                    return -1;
                --letters[prevChar];
            }
            if (ch != lastChar)
                ++letters[ch];
            else
                --currentNumberOfFrogs;
        }
        for (const auto &entry : letters)
        {
            if (entry.second != 0)
                return -1;
        }
        return static_cast<int>(numberOfFrogs);
    }
};

}

namespace MinNumberOfFrogsCroakingTask
{

TEST(MinNumberOfFrogsCroakingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minNumberOfFrogs("croakcroak"));
    ASSERT_EQ(2, solution.minNumberOfFrogs("crcoakroak"));
    ASSERT_EQ(-1, solution.minNumberOfFrogs("croakcrook"));
}

}