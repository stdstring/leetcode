#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumOperations(std::string const &num) const
    {
        // an integer x is considered special if it is divisible by 25 =>
        // special number has one of the following suffix 00, 25, 50, 75
        // or equals 0
        bool has5 = false;
        bool has0 = false;
        for (size_t rIndex = 0; rIndex < num.size(); ++rIndex)
        {
            const size_t index = num.size() - 1 - rIndex;
            switch (num[index])
            {
            case '0':
                if (has0)
                    return static_cast<int>(rIndex - 1);
                has0 = true;
                break;
            case '2':
            case '7':
                if (has5)
                    return static_cast<int>(rIndex - 1);
                break;
            case '5':
                if (has0)
                    return static_cast<int>(rIndex - 1);
                has5 = true;
                break;
            default:
                // do nothing
                break;
            }
        }
        return static_cast<int>(num.size() - (has0 ? 1 : 0));
    }
};

}

namespace MinOperationsToMakeSpecialNumberTask
{

TEST(MinOperationsToMakeSpecialNumberTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumOperations("2245047"));
    ASSERT_EQ(3, solution.minimumOperations("2908305"));
    ASSERT_EQ(1, solution.minimumOperations("10"));
}

}