#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void rotate(std::vector<int> &nums, int k) const
    {
        const size_t gcd = std::gcd(nums.size(), k);
        for (size_t start = 0; start < gcd; ++start)
        {
            size_t current = start;
            do
            {
                const size_t next = (current + k) % nums.size();
                std::swap(nums[start], nums[next]);
                current = next;
            }
            while (current != start);
        }
    }
};

}

namespace
{

void checkRotate(std::vector<int> const &source, int k, std::vector<int> const &expected)
{
    std::vector<int> nums(source);
    const Solution solution;
    solution.rotate(nums, k);
    ASSERT_EQ(expected, nums);
}

}

namespace RotateArrayTask
{

TEST(RotateArrayTaskTests, Examples)
{
    checkRotate({1, 2, 3, 4, 5, 6, 7}, 3, {5, 6, 7, 1, 2, 3, 4});
    checkRotate({-1, -100, 3, 99}, 2, {3, 99, -1, -100});
}

}