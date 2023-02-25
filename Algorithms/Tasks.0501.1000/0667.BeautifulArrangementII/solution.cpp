#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> constructArray(int n, int k) const
    {
        std::vector<int> arrangement;
        arrangement.reserve(n);
        for (int number = 1; number < n - k; number++)
            arrangement.push_back(number);
        int left = n - k;
        int right = n;
        while (right > left)
        {
            arrangement.push_back(left++);
            arrangement.push_back(right--);
        }
        if (right == left)
            arrangement.push_back(left);
        return arrangement;
    }
};

}

namespace BeautifulArrangementIITask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3}), solution.constructArray(3, 1));
    ASSERT_EQ(std::vector<int>({1, 3, 2}), solution.constructArray(3, 2));
}

TEST(TwoSumTaskTests, Custom)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4, 5}), solution.constructArray(5, 1));
    ASSERT_EQ(std::vector<int>({1, 2, 3, 5, 4}), solution.constructArray(5, 2));
    ASSERT_EQ(std::vector<int>({1, 2, 5, 3, 4}), solution.constructArray(5, 3));
    ASSERT_EQ(std::vector<int>({1, 5, 2, 4, 3}), solution.constructArray(5, 4));
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6}), solution.constructArray(6, 1));
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4, 6, 5}), solution.constructArray(6, 2));
    ASSERT_EQ(std::vector<int>({1, 2, 3, 6, 4, 5}), solution.constructArray(6, 3));
    ASSERT_EQ(std::vector<int>({1, 2, 6, 3, 5, 4}), solution.constructArray(6, 4));
    ASSERT_EQ(std::vector<int>({1, 6, 2, 5, 3, 4}), solution.constructArray(6, 5));
}

}