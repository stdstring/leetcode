#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool checkRecord(std::string const &s) const
    {
        bool hasAbsent = false;
        int currentContinuousCount = 0;
        for (char ch : s)
        {
            switch (ch)
            {
                case 'L':
                    ++currentContinuousCount;
                    if (currentContinuousCount > 2)
                        return false;
                    break;
                case 'A':
                    if (hasAbsent)
                        return false;
                    hasAbsent = true;
                default:
                    currentContinuousCount = 0;
            }
        }
        return true;
    }
};

}

namespace StudentAttendanceRecordITask
{

TEST(StudentAttendanceRecordITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.checkRecord("PPALLP"));
    ASSERT_EQ(false, solution.checkRecord("PPALLL"));
}

}