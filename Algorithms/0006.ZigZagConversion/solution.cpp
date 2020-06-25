#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string convert(std::string const &s, int numRows) const
    {
        if (numRows == 1)
            return s;
        const int zigzagSize = 2 * numRows - 2;
        std::string dest;
        // first line
        for (size_t index = 0; index < s.size(); index += zigzagSize)
            dest.push_back(s[index]);
        // intermediate lines
        for (int row = 2; row < numRows; ++row)
        {
            for (size_t index = 0; index < s.size(); index += zigzagSize)
            {
                if ((index + row - 1) < s.size())
                    dest.push_back(s[index + row - 1]);
                if ((index + zigzagSize - row + 1) < s.size())
                    dest.push_back(s[index + zigzagSize - row + 1]);
            }
        }
        // last line
        for (size_t index = numRows - 1; index < s.size(); index += zigzagSize)
            dest.push_back(s[index]);
        return dest;
    }
};

}

namespace ZigZagConversionTask
{

TEST(ZigZagConversionTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("PAHNAPLSIIGYIR", solution.convert("PAYPALISHIRING", 3));
    ASSERT_EQ("PINALSIGYAHRPI", solution.convert("PAYPALISHIRING", 4));
}

TEST(ZigZagConversionTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("A", solution.convert("A", 1));
}

}