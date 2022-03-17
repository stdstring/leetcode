#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int kthFactor(int n, int k) const
    {
        std::vector<int> smallFactors;
        std::vector<int> bigFactors;
        int number = 1;
        while (number * number <= n)
        {
            if (n % number == 0)
            {
                smallFactors.push_back(number);
                int bigFactor = n / number;
                if (bigFactor != number)
                    bigFactors.push_back(bigFactor);
            }
            ++number;
        }
        const size_t factorNumber = k;
        if ((smallFactors.size() + bigFactors.size()) < factorNumber)
            return -1;
        if (factorNumber <= smallFactors.size())
            return smallFactors[factorNumber - 1];
        return bigFactors[bigFactors.size() - (k - smallFactors.size())];
    }
};

}

namespace KthFactorOfNTask
{

TEST(KthFactorOfNTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.kthFactor(12, 3));
    ASSERT_EQ(7, solution.kthFactor(7, 2));
    ASSERT_EQ(-1, solution.kthFactor(4, 4));
}


}