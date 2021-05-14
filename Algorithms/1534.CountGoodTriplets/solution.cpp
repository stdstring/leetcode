#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countGoodTriplets(std::vector<int> const &arr, int a, int b, int c) const
    {
        size_t goodTripletsCount = 0;
        for (size_t i = 0; i < arr.size() - 2; ++i)
        {
            for (size_t j = i + 1; j < arr.size() - 1; ++j)
            {
                const int delta1 = std::abs(arr[i] - arr[j]);
                if (delta1 > a)
                    continue;
                for (size_t k = j + 1; k < arr.size(); ++k)
                {
                    const int delta2 = std::abs(arr[j] - arr[k]);
                    const int delta3 = std::abs(arr[i] - arr[k]);
                    if ((delta2 <= b) && (delta3 <= c))
                        ++goodTripletsCount;
                }
            }
        }
        return static_cast<int>(goodTripletsCount);
    }
};

}

namespace CountGoodTripletsTask
{

TEST(CountGoodTripletsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.countGoodTriplets({3, 0, 1, 1, 9, 7}, 7, 2, 3));
    ASSERT_EQ(0, solution.countGoodTriplets({1, 1, 2, 2, 3}, 0, 0, 1));
}

}