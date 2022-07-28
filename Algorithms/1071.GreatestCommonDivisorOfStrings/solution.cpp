#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string gcdOfStrings(std::string const &str1, std::string const &str2) const
    {
        std::string const &smallString = str1.size() <= str2.size() ? str1 : str2;
        std::string const &bigString = str1.size() <= str2.size() ? str2 : str1;
        std::string gcdString;
        for (size_t prefixSize = 1; prefixSize <= smallString.size(); ++prefixSize)
        {
            if (checkPrefix(smallString, smallString, prefixSize) && checkPrefix(bigString, smallString, prefixSize))
                gcdString = smallString.substr(0, prefixSize);
        }
        return gcdString;
    }

private:
    [[nodiscard]] bool checkPrefix(std::string const &checkedStr, std::string const &source, size_t prefixSize) const
    {
        if ((checkedStr.size() % prefixSize) != 0)
            return false;
        const size_t partsCount = checkedStr.size() / prefixSize;
        for (size_t index = 0; index < prefixSize; ++index)
        {
            for (size_t part = 0; part < partsCount; ++part)
            {
                if (source[index] != checkedStr[part * prefixSize + index])
                    return false;
            }
        }
        return true;
    }
};

}

namespace GreatestCommonDivisorOfStringsTask
{

TEST(GreatestCommonDivisorOfStringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("ABC", solution.gcdOfStrings("ABCABC", "ABC"));
    ASSERT_EQ("AB", solution.gcdOfStrings("ABABAB", "ABAB"));
    ASSERT_EQ("", solution.gcdOfStrings("LEET", "CODE"));
}

}