#include <algorithm>
#include <cstdint>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> splitIntoFibonacci(std::string const &source) const
    {
        if ((source.size() < 3) || (source[0] == '0' && source[1] == '0' && source[2] != '0'))
            return {};
        std::vector<int> digits(source.size(), 0);
        std::transform(source.cbegin(), source.cend(), digits.begin(), [](char ch){ return ch - '0'; });
        size_t firstSize = 1;
        size_t secondSize = 1;
        while (2 * firstSize + 1 <= digits.size())
        {
            const uint64_t first = createNumber(digits, 0, firstSize);
            const uint64_t second = createNumber(digits, firstSize, secondSize);
            if (first > INT_MAX)
                return {};
            if (second > INT_MAX)
            {
                ++firstSize;
                secondSize = 1;
                continue;
            }
            std::vector<int> sequence(tryGenerateSequence(static_cast<int>(first), static_cast<int>(second), digits, firstSize + secondSize));
            if (!sequence.empty())
                return sequence;
            ++secondSize;
            if (digits[firstSize] == 0 || firstSize + secondSize + std::max(firstSize, secondSize) > digits.size())
            {
                ++firstSize;
                secondSize = 1;
            }
        }
        return {};
    }

private:
    uint64_t createNumber(std::vector<int> const &digits, size_t start, size_t size) const
    {
        uint64_t number = 0;
        for (size_t shift = 0; shift < size; ++shift)
            number =  10 * number + digits[start + shift];
        return number;
    }

    std::vector<int> tryGenerateSequence(int first, int second, std::vector<int> const &digits, size_t start) const
    {
        std::vector<int> sequence;
        sequence.push_back(first);
        sequence.push_back(second);
        uint64_t prevNumber = first;
        uint64_t currentNumber = second;
        for (size_t index = start; index < digits.size();)
        {
            const uint64_t expectedNextNumber = prevNumber + currentNumber;
            if (expectedNextNumber > INT_MAX)
                return {};
            uint64_t actualNextNumber = 0;
            if (digits[index] == 0)
                ++index;
            else
            {
                while (index < digits.size() && actualNextNumber < expectedNextNumber)
                    actualNextNumber = 10 * actualNextNumber + digits[index++];
            }
            if (expectedNextNumber != actualNextNumber)
                return {};
            sequence.push_back(static_cast<int>(actualNextNumber));
            prevNumber = currentNumber;
            currentNumber = actualNextNumber;
        }
        return sequence;
    }
};

}

namespace SplitArrayIntoFibonacciSequenceTask
{

TEST(SplitArrayIntoFibonacciSequenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({123, 456, 579}), solution.splitIntoFibonacci("123456579"));
    ASSERT_EQ(std::vector<int>({1, 1, 2, 3, 5, 8, 13}), solution.splitIntoFibonacci("11235813"));
    ASSERT_EQ(std::vector<int>(), solution.splitIntoFibonacci("112358130"));
    ASSERT_EQ(std::vector<int>(), solution.splitIntoFibonacci("0123"));
    ASSERT_EQ(std::vector<int>({11, 0, 11, 11}), solution.splitIntoFibonacci("1101111"));
}

TEST(SplitArrayIntoFibonacciSequenceTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>(), solution.splitIntoFibonacci("00246"));
    ASSERT_EQ(std::vector<int>(), solution.splitIntoFibonacci("214748364721474836422147483641"));
}

}