#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int titleToNumber(std::string const &s) const
    {
        const int alphabetSize = 26;
        int result = 0;
        for(char ch : s)
        {
            result = result * alphabetSize;
            result += (ch - 'A' + 1);
        }
        return result;
    }
};

}

namespace ExcelSheetColumnNumberTask
{

TEST(ExcelSheetColumnNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.titleToNumber("A"));
    ASSERT_EQ(28, solution.titleToNumber("AB"));
    ASSERT_EQ(701, solution.titleToNumber("ZY"));
}

}