#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumOneBitOperations(int n) const
    {
        // 1)
        //    Observe the numbers for 2 ^ k
        //    f(0) = 0: "000"
        //    f(1) = 1 : "001" <->["000"]
        //    f(2) = 3 : "010" < -> "011" < ->["001" < -> "000"]
        //    f(3) = 7 : "100" < -> "101" < -> "111" < -> "110" < ->["010" < -> "011" < -> "001" < -> "000"]
        //    We can conclude that :
        //        a) all transformations are reversible
        //        b) f(2 ^ k) = (2 ^ (k + 1)) - 1
        // 2)
        //    look at "101" and "111"
        //    we can convert it into "110", and transform it into "010" which is 2 ^ k
        //    so we can convert them into sub - problems
        //    f(0b101) = 2 + 1 + f(0b010)
        //    2 is for "101" < -> "111" < -> "110"
        //    1 is for "110" < -> "010"
        //    f(0b111) = 1 + 1 + f(0b010)
        //    1 is for "111" < -> "110"
        //    1 is for "110" < -> "010"
        std::unordered_map<int, int> dp({{0, 0}, {1, 1}});
        return minimumOneBitOperations(n, dp);
    }

private:
    [[nodiscard]] int minimumOneBitOperations(int n, std::unordered_map<int, int> &dp) const
    {
        const auto iterator = dp.find(n);
        if (iterator != dp.cend())
            return iterator->second;
        const int leftmostBit = getLeftmostBit(n);
        const int nextBit = leftmostBit - 1;
        const int maskLeftmost11 = (1 << leftmostBit) | (1 << nextBit);
        // convert n to maskLeftmost11
        const int ops1 = minimumOneBitOperations(n ^ maskLeftmost11, dp);
        // convert maskLeftmost11 to 2^nextBit
        const int ops2 = 1;
        // convert 2^nextBit to 0
        const int ops3 = (1 << (nextBit + 1)) - 1;
        return ops1 + ops2 + ops3;
    }

    [[nodiscard]] int getLeftmostBit(int n) const
    {
        int bit = 0;
        while (n > 1)
        {
            ++bit;
            n >>= 1;
        }
        return bit;
    }
};

}

namespace MinOneBitOperationsMakeIntegersZeroTask
{

TEST(MinOneBitOperationsMakeIntegersZeroTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumOneBitOperations(3));
    ASSERT_EQ(4, solution.minimumOneBitOperations(6));
}

}