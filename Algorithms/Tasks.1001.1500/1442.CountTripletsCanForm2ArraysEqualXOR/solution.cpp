#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countTriplets(std::vector<int> const &arr) const
    {
        std::vector<int> prefixSum(arr.size() + 1, 0);
        for (size_t index = 0; index < arr.size(); ++index)
            prefixSum[index + 1] = (index > 0 ? prefixSum[index] : 0) ^ arr[index];
        size_t tripletsCount = 0;
        for (size_t start = 0; start < prefixSum.size(); ++start)
        {
            for (size_t end = start + 1; end < prefixSum.size(); ++end)
            {
                if (prefixSum[start] == prefixSum[end])
                    tripletsCount += (end - start- 1);
            }
        }
        return static_cast<int>(tripletsCount);
    }
};

}

namespace CountTripletsCanForm2ArraysEqualXORTask
{

TEST(CountTripletsCanForm2ArraysEqualXORTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countTriplets({2, 3, 1, 6, 7}));
    ASSERT_EQ(10, solution.countTriplets({1, 1, 1, 1, 1}));
}

}