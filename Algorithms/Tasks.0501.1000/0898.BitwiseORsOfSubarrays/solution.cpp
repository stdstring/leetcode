#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int subarrayBitwiseORs(std::vector<int> const &arr) const
    {
        // (a1)
        // (a2) (a2 a1)
        // (a3) (a3 a2) (a3 a2 a1)
        // (a4) (a4 a3) (a4 a3 a2) (a4 a3 a2 a1)
        // ...
        // Each row comes from adding the new element, and let the new element pair up with each one in the last row.
        // Each element is either equal to its left one, or has one more '1' in it. So each row has at most 32 numbers.
        std::vector<int> subarrays;
        size_t start = 0;
        size_t end = 0;
        for (int number : arr)
        {
            subarrays.push_back(number);
            for (size_t index = start; index < end; ++index)
            {
                int orValue = number | subarrays[index];
                if (orValue != subarrays.back())
                    subarrays.push_back(orValue);
            }
            start = end;
            end = subarrays.size();
        }
        return static_cast<int>(std::unordered_set<int>(subarrays.cbegin(), subarrays.cend()).size());
    }
};

}

namespace BitwiseORsOfSubarraysTask
{

TEST(BitwiseORsOfSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.subarrayBitwiseORs({0}));
    ASSERT_EQ(3, solution.subarrayBitwiseORs({1, 1, 2}));
    ASSERT_EQ(6, solution.subarrayBitwiseORs({1, 2, 4}));
}

}
