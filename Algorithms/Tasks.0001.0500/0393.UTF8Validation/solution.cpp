#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool validUtf8(std::vector<int> const &data) const
    {
        size_t charStart = 0;
        while (charStart < data.size())
        {
            const size_t octetCount = calcOctetCount(data[charStart]);
            if (octetCount == 0 || (charStart + octetCount) > data.size())
                return false;
            if (!checkOtherOctets(data, charStart, octetCount))
                return false;
            charStart += octetCount;
        }
        return true;
    }

private:
    size_t calcOctetCount(int firstOctet) const
    {
        if ((firstOctet & 0b10000000) == 0)
            return 1;
        if ((firstOctet & 0b11100000) == 0b11000000)
            return 2;
        if ((firstOctet & 0b11110000) == 0b11100000)
            return 3;
        if ((firstOctet & 0b11111000) == 0b11110000)
            return 4;
        return 0;
    }

    bool checkOtherOctets(std::vector<int> const &data, size_t charStart, size_t octetCount) const
    {
        for(size_t index = charStart + 1; index < charStart + octetCount; ++index)
        {
            if ((data[index] & 0b11000000) != 0b10000000)
                return false;
        }
        return true;
    }
};

}

namespace UTF8ValidationTask
{

TEST(UTF8ValidationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.validUtf8({197, 130, 1}));
    ASSERT_EQ(false, solution.validUtf8({235, 140, 4}));
}

TEST(UTF8ValidationTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.validUtf8({240, 162, 138, 147, 145}));
}

}