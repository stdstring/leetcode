#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int checkRecord(int n) const
    {
        const int modValue = 1000000007;
        int normalCount = 1;
        int oneLateEndCount = 1;
        int twoLateEndCount = 0;
        int hasAbsentCount = 1;
        int oneLateEndWithAbsentCount = 0;
        int twoLateEndWithAbsentCount = 0;
        for (size_t size = 1; size < static_cast<size_t>(n); ++size)
        {
            // normal
            const int nextNormalCount = ((normalCount + oneLateEndCount) % modValue + twoLateEndCount) % modValue;
            // one 'L' on end
            const int nextOneLateEndCount = normalCount;
            // two 'L' on end
            const int nextTwoLateEndCount = oneLateEndCount;
            // has 'A'
            int nextHasAbsentCount = ((normalCount + oneLateEndCount) % modValue + twoLateEndCount) % modValue;
            nextHasAbsentCount = (nextHasAbsentCount + hasAbsentCount) % modValue;
            nextHasAbsentCount = (nextHasAbsentCount + oneLateEndWithAbsentCount) % modValue;
            nextHasAbsentCount = (nextHasAbsentCount + twoLateEndWithAbsentCount) % modValue;
            // has 'A' & one 'L' on end
            const int nextOneLateEndWithAbsentCount = hasAbsentCount;
            // has 'A' & two 'L' on end
            const int nextTwoLateEndWithAbsentCount = oneLateEndWithAbsentCount;
            // update
            normalCount = nextNormalCount;
            oneLateEndCount = nextOneLateEndCount;
            twoLateEndCount = nextTwoLateEndCount;
            hasAbsentCount = nextHasAbsentCount;
            oneLateEndWithAbsentCount = nextOneLateEndWithAbsentCount;
            twoLateEndWithAbsentCount = nextTwoLateEndWithAbsentCount;
        }
        return (((normalCount + oneLateEndCount) % modValue + twoLateEndCount) % modValue + ((hasAbsentCount + oneLateEndWithAbsentCount) % modValue + twoLateEndWithAbsentCount) % modValue) % modValue;
    }
};

}

namespace StudentAttendanceRecordIITask
{

TEST(StudentAttendanceRecordIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(8, solution.checkRecord(2));
}

TEST(StudentAttendanceRecordIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(19, solution.checkRecord(3));
    ASSERT_EQ(985598218, solution.checkRecord(100));
}

}