#include <algorithm>
#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int lengthAfterTransformations(std::string const &s, int t) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetEnd = 'z' - alphabetStart;
        constexpr int modValue = 1000000007;
        std::array<int, alphabetSize> current;
        current.fill(0);
        std::array<int, alphabetSize> next;
        next.fill(0);
        // init
        for (const char ch : s)
            ++current[ch - alphabetStart];
        // transform
        for (int iteration = 1; iteration <=t; ++iteration)
        {
            for (size_t letter = 0; letter < alphabetEnd; ++letter)
                next[letter + 1] = current[letter];
            next[0] = current[alphabetEnd];
            next[1] = (next[1] + current[alphabetEnd]) % modValue;
            std::swap(current, next);
            next.fill(0);
        }
        // result
        int result = 0;
        for (int count : current)
            result = (result + count) % modValue;
        return result;
    }
};

}

namespace TotalCharactersAfterTransform1Task
{

TEST(TotalCharactersAfterTransform1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.lengthAfterTransformations("abcyy", 2));
    ASSERT_EQ(5, solution.lengthAfterTransformations("azbk", 1));
}

}