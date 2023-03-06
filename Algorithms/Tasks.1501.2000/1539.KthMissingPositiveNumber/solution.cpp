#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findKthPositive(std::vector<int> const &arr, int k) const
    {
        const int freeNumbersInArr = static_cast<int>(arr.back() - arr.size());
        if (k <= freeNumbersInArr)
        {
            int current = 1;
            for (size_t index = 0; index < arr.size();)
            {
                if (current == arr[index])
                    ++index;
                else
                {
                    if (k == 1)
                        return current;
                    --k;
                }
                ++current;
            }
            return -1;
        }
        return arr.back() + (k - freeNumbersInArr);
    }
};

}

namespace KthMissingPositiveNumberTask
{

TEST(KthMissingPositiveNumberTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.findKthPositive({2, 3, 4, 7, 11}, 5));
    ASSERT_EQ(6, solution.findKthPositive({1, 2, 3, 4}, 2));
}

}