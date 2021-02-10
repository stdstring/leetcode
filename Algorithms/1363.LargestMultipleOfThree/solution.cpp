#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string largestMultipleOfThree(std::vector<int> const &digits) const
    {
        std::array<size_t, 10> digitsData{};
        digitsData.fill(0);
        int digitsSum = 0;
        for (int digit : digits)
        {
            ++digitsData[digit];
            digitsSum += digit;
        }
        correctDigits(digitsData, digitsSum);
        if (digitsSum == 0)
            return digitsData[0] > 0 ? "0" : "";
        std::string dest;
        for (int digit = 9; digit >= 0; --digit)
            dest.append(digitsData[digit], static_cast<char>('0' + digit));
        return dest;
    }

private:
    void correctDigits(std::array<size_t, 10> &digitsData, int &digitsSum) const
    {
        if (digitsSum % 3 == 0)
            return;
        for (int rest = digitsSum % 3; rest < 9; rest += 3)
        {
            if (digitsData[rest] > 0)
            {
                --digitsData[rest];
                digitsSum -= rest;
                return;
            }
        }
        std::vector<std::pair<int, int>> restPairs;
        if (digitsSum % 3 == 1)
            restPairs = {{2, 2}, {2, 5}, {5, 5}, {2, 8}, {5, 8}, {8, 8}};
        else
            restPairs = {{1, 1}, {1, 4}, {4, 4}, {1, 7}, {4, 7}, {7, 7}};
        for (std::pair<int, int> const &restPair : restPairs)
        {
            if ((restPair.first == restPair.second && digitsData[restPair.first] > 1) || (restPair.first != restPair.second && digitsData[restPair.first] > 0 && digitsData[restPair.second] > 0))
            {
                --digitsData[restPair.first];
                --digitsData[restPair.second];
                digitsSum -= (restPair.first + restPair.second);
            }
        }
    }
};

}

namespace LargestMultipleOfThreeTask
{

TEST(LargestMultipleOfThreeTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("981", solution.largestMultipleOfThree({8, 1, 9}));
    ASSERT_EQ("8760", solution.largestMultipleOfThree({8, 6, 7, 1, 0}));
    ASSERT_EQ("", solution.largestMultipleOfThree({1}));
    ASSERT_EQ("0", solution.largestMultipleOfThree({0, 0, 0, 0, 0, 0}));
}

TEST(LargestMultipleOfThreeTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("", solution.largestMultipleOfThree({5, 8}));
}

}

