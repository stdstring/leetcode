#include <array>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int superPow(int a, std::vector<int> const &b) const
    {
        std::array<int, 10> aPowers{};
        aPowers[0] = 1;
        for (size_t digit = 1; digit < 10; ++digit)
            aPowers[digit] = (aPowers[digit - 1] * (a % ModValue)) % ModValue;
        int result = 1;
        for (int digit : b)
            result = (calcTenPower(result) * aPowers[digit]) % ModValue;
        return result;
    }

private:
    static constexpr int ModValue = 1337;

    int calcTenPower(int value) const
    {
        if (value == 1)
            return 1;
        const int squareValue = (value * value) % ModValue;
        const int fourthValue = (squareValue * squareValue) % ModValue;
        const int eighthValue = (fourthValue * fourthValue) % ModValue;
        return (eighthValue * squareValue) % ModValue;
    }
};

}

namespace SuperPowTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(8, solution.superPow(2, {3}));
    ASSERT_EQ(1024, solution.superPow(2, {1, 0}));
    ASSERT_EQ(1, solution.superPow(1, {4, 3, 3, 8, 5, 2}));
    ASSERT_EQ(1198, solution.superPow(2147483647, {2, 0, 0}));
}

}