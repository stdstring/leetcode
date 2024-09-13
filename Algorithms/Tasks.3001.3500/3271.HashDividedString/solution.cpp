#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string stringHash(std::string const &s, int k) const
    {
        constexpr int alphabetStart = 'a';
        constexpr int alphabetSize = 26;
        const size_t portionSize = k;
        const size_t resultSize = s.size() / k;
        std::string result(resultSize, ' ');
        int portion = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            const size_t size = index + 1;
            portion += (s[index] - alphabetStart);
            if ((size % portionSize) == 0)
            {
                result[(size / portionSize) - 1] = static_cast<char>(alphabetStart + (portion % alphabetSize));
                portion = 0;
            }
        }
        return result;
    }
};

}

namespace HashDividedStringTask
{

TEST(HashDividedStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("bf", solution.stringHash("abcd", 2));
    ASSERT_EQ("i", solution.stringHash("mxz", 3));
}

}