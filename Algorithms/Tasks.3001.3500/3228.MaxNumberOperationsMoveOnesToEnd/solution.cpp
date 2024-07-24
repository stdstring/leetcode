#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxOperations(std::string const &s) const
    {
        const size_t lastIndex = s.size() - 1;
        size_t onesCount = 0;
        size_t operationsCount = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] == '0')
            {
                if ((index == lastIndex) || (s[index + 1] == '1'))
                    operationsCount += onesCount;
            }
            if (s[index] == '1')
                ++onesCount;
        }
        return static_cast<int>(operationsCount);
    }
};

}

namespace MaxNumberOperationsMoveOnesToEndTask
{

TEST(MaxNumberOperationsMoveOnesToEndTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxOperations("1001101"));
    ASSERT_EQ(0, solution.maxOperations("00111"));
}

}