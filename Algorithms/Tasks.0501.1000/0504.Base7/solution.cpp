#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string convertToBase7(int num) const
    {
        std::string buf;
        std::div_t dv;
        dv.quot = num;
        do {
            dv = std::div(dv.quot, 7);
            buf += "0123456"[std::abs(dv.rem)];
        } while(dv.quot);
        if(num < 0) buf += '-';
        return {buf.rbegin(), buf.rend()};
    }
};

}

namespace Base7Task
{

TEST(Base7TaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("202", solution.convertToBase7(100));
    ASSERT_EQ("-10", solution.convertToBase7(-7));
}

}