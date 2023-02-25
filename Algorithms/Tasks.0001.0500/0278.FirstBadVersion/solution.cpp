#include "gtest/gtest.h"

namespace
{

// TODO (std_string) : think about smarter approach
int firstBadVersionValue = 0;

// The API isBadVersion is defined for you.
bool isBadVersion(int version)
{
    return version >= firstBadVersionValue;
}

}

namespace
{

class Solution
{
public:
    int firstBadVersion(int n) const
    {
        if (isBadVersion(1))
            return 1;
        int left = 1;
        int right = n;
        while (right - left > 1)
        {
            const int middle = static_cast<int>((0ll + right + left) / 2);
            if (isBadVersion(middle))
                right = middle;
            else
                left = middle;
        }
        return right;
    }
};

}

namespace FirstBadVersionTask
{

TEST(FirstBadVersionTaskTests, Examples)
{
    const Solution solution;
    firstBadVersionValue = 4;
    ASSERT_EQ(4, solution.firstBadVersion(5));
}

TEST(FirstBadVersionTaskTests, FromWrongAnswers)
{
    const Solution solution;
    firstBadVersionValue = 1702766719;
    ASSERT_EQ(1702766719, solution.firstBadVersion(2126753390));
}

}