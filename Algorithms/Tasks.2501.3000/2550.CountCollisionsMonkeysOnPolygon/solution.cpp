#include <cstdint>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int monkeyMove(int n) const
    {
        const uint64_t movesCount = calc2Power(n);
        return static_cast<int>((movesCount + ModValue - 2) % ModValue);
    }

private:
    static constexpr uint64_t ModValue = 1000000007;

    [[nodiscard]] uint64_t calc2Power(int n) const
    {
        if (n == 1)
            return 2;
        const uint64_t result = calc2Power(n / 2);
        return (result * result * (n % 2 == 0 ? 1 : 2)) % ModValue;
    }
};

}

namespace CountCollisionsMonkeysOnPolygonTask
{

TEST(CountCollisionsMonkeysOnPolygonTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.monkeyMove(3));
    ASSERT_EQ(14, solution.monkeyMove(4));
}

TEST(CountCollisionsMonkeysOnPolygonTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(30, solution.monkeyMove(5));
    ASSERT_EQ(62, solution.monkeyMove(6));
    ASSERT_EQ(976371283, solution.monkeyMove(100));
    ASSERT_EQ(688423208, solution.monkeyMove(1000));
}

}