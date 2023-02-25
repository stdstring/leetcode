#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<bool> prefixesDivBy5(std::vector<int> const &A) const
    {
        int result = 0;
        std::vector<bool> dest;
        dest.reserve(A.size());
        for (int value : A)
        {
            result = (2 * result + value) % 5;
            dest.push_back(result == 0);
        }
        return dest;
    }
};

}

namespace BinaryPrefixDivisibleBy5Task
{

TEST(BinaryPrefixDivisibleBy5TaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<bool>({true, false, false}), solution.prefixesDivBy5({0, 1, 1}));
    ASSERT_EQ(std::vector<bool>({false, false, false}), solution.prefixesDivBy5({1, 1, 1}));
    ASSERT_EQ(std::vector<bool>({true, false, false, false, true, false}), solution.prefixesDivBy5({0, 1, 1, 1, 1, 1}));
    ASSERT_EQ(std::vector<bool>({false, false, false, false, false}), solution.prefixesDivBy5({1, 1, 1, 0, 1}));
}

}