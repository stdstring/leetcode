#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isAdditiveNumber(std::string const &num) const
    {
        if (num.size() < 3)
            return false;
        return processFirstNumber(num);
    }

private:
    bool processFirstNumber(std::string const &num) const
    {
        if (num[0] == '0')
            return processSecondNumber(num, 1, 0);
        long long firstNumber = 0;
        for (size_t index = 0; index < num.size() / 2; ++index)
        {
            firstNumber = 10 * firstNumber + static_cast<long long>(num[index]) - '0';
            if (processSecondNumber(num, index + 1, firstNumber))
                return true;
        }
        return false;
    }

    bool processSecondNumber(std::string const &num, size_t start, long long firstNumber) const
    {
        if (num[start] == '0')
            return checkSequence(num, start + 1, 0, firstNumber);
        long long secondNumber = 0;
        for (size_t index = start; index < start + (num.size() - start) / 2; ++index)
        {
            secondNumber = 10 * secondNumber + static_cast<long long>(num[index]) - '0';
            if (checkSequence(num, index + 1, secondNumber, firstNumber + secondNumber))
                return true;
        }
        return false;
    }

    bool checkSequence(std::string const &num, size_t index, long long prevNumber, long long sum) const
    {
        if (index == num.size())
            return true;
        if (num[index] == '0')
            return sum == 0 ? checkSequence(num, index + 1, 0, prevNumber) : false;
        long long number = static_cast<long long>(num[index++]) - '0';
        while (index < num.size() && number < sum)
            number = 10 * number + static_cast<long long>(num[index++]) - '0';
        return number == sum ? checkSequence(num, index, number, prevNumber + number) : false;
    }
};

}

namespace AdditiveNumberTask
{

TEST(AdditiveNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isAdditiveNumber("112358"));
    ASSERT_EQ(true, solution.isAdditiveNumber("199100199"));
    ASSERT_EQ(false, solution.isAdditiveNumber("1203"));
    ASSERT_EQ(false, solution.isAdditiveNumber("1023"));
}

TEST(AdditiveNumberTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isAdditiveNumber("111"));
    ASSERT_EQ(true, solution.isAdditiveNumber("199111992"));
    ASSERT_EQ(true, solution.isAdditiveNumber("211738"));
    ASSERT_EQ(true, solution.isAdditiveNumber("000"));
    ASSERT_EQ(true, solution.isAdditiveNumber("0000"));
    ASSERT_EQ(true, solution.isAdditiveNumber("101"));
}

}