#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> grayCode(int n) const
    {
        std::vector<int> result;
        result.push_back(0);
        for (int number = 1; number < (1 << n) ; ++number)
        {
            int index = 0;
            int current = number;
            while (current % 2 == 0)
            {
                ++index;
                current /= 2;
            }
            const int mask = 1 << index;
            if ((result.back() & mask) == 0)
                result.push_back(result.back() | mask);
            else
                result.push_back(result.back() & (~mask));
        }
        return result;
    }
};

}

namespace GrayCodeTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 3, 2}), solution.grayCode(2));
    ASSERT_EQ(std::vector<int>({0, 1}), solution.grayCode(1));
}

}