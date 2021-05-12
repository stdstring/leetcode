#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int kthGrammar(int n, int k) const
    {
        --k;
        int kthSymbol = 0;
        int delta = 1 << (n - 1);
        for (int step = 1; step < n; ++step)
        {
            delta /= 2;
            const bool isFirstPart = k < delta;
            if (k >= delta)
                k -= delta;
            if (kthSymbol == 0)
                kthSymbol = isFirstPart ? 0 : 1;
            else
                kthSymbol = isFirstPart ? 1 : 0;
        }
        return kthSymbol;
    }
};

}

namespace KthSymbolInGrammarTask
{

TEST(KthSymbolInGrammarTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(0, solution.kthGrammar(1, 1));
    ASSERT_EQ(0, solution.kthGrammar(2, 1));
    ASSERT_EQ(1, solution.kthGrammar(2, 2));
    ASSERT_EQ(1, solution.kthGrammar(4, 5));
}

}