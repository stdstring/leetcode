#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> addToArrayForm(std::vector<int> const &num, int k) const
    {
        std::vector<int> result;
        auto iterator = num.crbegin();
        bool carry = false;
        while (iterator != num.crend() || k != 0)
        {
            const int sum = (iterator == num.crend() ? 0 : *iterator) + (k % 10) + (carry ? 1 : 0);
            result.push_back(sum % 10);
            carry = (sum / 10) > 0;
            if (iterator != num.crend())
                ++iterator;
            k /= 10;
        }
        if (carry)
            result.push_back(1);
        std::reverse(result.begin(), result.end());
        return result;
    }
};

}

namespace AddToArrayFormOfIntegerTask
{

TEST(AddToArrayFormOfIntegerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4}), solution.addToArrayForm({1, 2, 0, 0}, 34));
    ASSERT_EQ(std::vector<int>({4, 5, 5}), solution.addToArrayForm({2, 7, 4}, 181));
    ASSERT_EQ(std::vector<int>({1, 0, 2, 1}), solution.addToArrayForm({2, 1, 5}, 806));
    ASSERT_EQ(std::vector<int>({1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}), solution.addToArrayForm({9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, 1));
}

}
