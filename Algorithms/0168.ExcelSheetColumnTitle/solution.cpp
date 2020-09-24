#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string convertToTitle(int n) const
    {
        const int alphabetSize = 26;
        std::string dest;
        while (n > 0)
        {
            --n;
            dest.insert(0, 1, 'A' + (n % alphabetSize));
            n /= alphabetSize;
        }
        return dest;
    }
};

}

namespace ExcelSheetColumnTitleTask
{

TEST(ExcelSheetColumnTitleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("A", solution.convertToTitle(1));
    ASSERT_EQ("AB", solution.convertToTitle(28));
    ASSERT_EQ("ZY", solution.convertToTitle(701));
}

TEST(ExcelSheetColumnTitleTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("AA", solution.convertToTitle(27));
}

}