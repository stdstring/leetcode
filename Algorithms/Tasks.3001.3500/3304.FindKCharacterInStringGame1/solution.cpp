#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] char kthCharacter(int k) const
    {
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        const size_t characterIndex = k - 1;
        std::string current("a");
        while (characterIndex >= current.size())
        {
            const size_t currentSize = current.size();
            for (size_t index = 0; index < currentSize; ++index)
            {
                const char nextChar = static_cast<char>(alphabetStart + (current[index] - alphabetStart + 1) % alphabetSize);
                current.push_back(nextChar);
            }
        }
        return current[characterIndex];
    }
};

}

namespace FindKCharacterInStringGame1Task
{

TEST(FindKCharacterInStringGame1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ('b', solution.kthCharacter(5));
    ASSERT_EQ('c', solution.kthCharacter(10));
}

TEST(FindKCharacterInStringGame1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ('b', solution.kthCharacter(3));
}

}