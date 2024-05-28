#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string getHappyString(int n, int k) const
    {
        const int maxNumber = power(3, n) - 1;
        int happyStringNumber = 0;
        for (int number = 0; number <= maxNumber; ++number)
        {
            std::string destString(generateString(number, 3, n));
            if (isHappy(destString))
                ++happyStringNumber;
            if (happyStringNumber == k)
                return destString;
        }
        return "";
    }

private:
    [[nodiscard]] int power(int base, int exp) const
    {
        int result = 1;
        for (int step = 1; step <= exp; ++step)
            result *= base;
        return result;
    }

    [[nodiscard]] std::string generateString(int number, int base, size_t size) const
    {
        std::string result(size, ' ');
        for (size_t index = 0; index < size; ++index)
        {
            result[size - 1 - index] = static_cast<char>('a' + (number % base));
            number /= base;
        }
        return result;
    }

    [[nodiscard]] bool isHappy(std::string const &source) const
    {
        for (size_t index = 1; index < source.size(); ++index)
        {
            if (source[index] == source[index - 1])
                return false;
        }
        return true;
    }
};

}

namespace KLexStringOfAllHappyStringsLengthNTask
{

TEST(KLexStringOfAllHappyStringsLengthNTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("c", solution.getHappyString(1, 3));
    ASSERT_EQ("", solution.getHappyString(1, 4));
    ASSERT_EQ("cab", solution.getHappyString(3, 9));
}

}