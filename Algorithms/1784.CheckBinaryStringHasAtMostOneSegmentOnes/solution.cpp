#include <string>

#include "gtest/gtest.h"

namespace
{
class Solution {
public:
    bool checkOnesSegment(std::string const &s) const
    {
        bool hasOneFinish = false;
        for (char ch : s)
        {
            switch (ch)
            {
                case '0':
                    hasOneFinish = true;
                    break;
                case '1':
                    if (hasOneFinish)
                        return false;
                    break;
                default: ;
            }
        }
        return true;
    }
};

}

namespace CheckBinaryStringHasAtMostOneSegmentOnesTask
{

TEST(CheckBinaryStringHasAtMostOneSegmentOnesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.checkOnesSegment("1001"));
    ASSERT_EQ(true, solution.checkOnesSegment("110"));
}

TEST(CheckBinaryStringHasAtMostOneSegmentOnesTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.checkOnesSegment("1"));
    ASSERT_EQ(true, solution.checkOnesSegment("10"));
}

}