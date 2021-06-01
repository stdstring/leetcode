#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int nextGreaterElement(int n) const
    {
        // digits
        std::vector<int> digits;
        while (n > 0)
        {
            digits.push_back(n % 10);
            n /= 10;
        }
        std::reverse(digits.begin(), digits.end());
        // next permutation
        if (!std::next_permutation(digits.begin(), digits.end()))
            return -1;
        // number
        long long result = 0;
        for (int digit : digits)
            result = result * 10 + digit;
        return result > INT_MAX ? -1 : static_cast<int>(result);
    }
};

}


namespace NextGreaterElementIIITask
{

TEST(NextGreaterElementIIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(21, solution.nextGreaterElement(12));
    ASSERT_EQ(-1, solution.nextGreaterElement(21));
}

TEST(NextGreaterElementIIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(-1, solution.nextGreaterElement(2147483486));
}

}