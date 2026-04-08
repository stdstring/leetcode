#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int xorAfterQueries(std::vector<int> const &nums, std::vector<std::vector<int>> const &queries) const
    {
        constexpr int modValue = 1000000007;
        std::vector<int> result(nums);
        for (std::vector<int> const &query : queries)
        {
            int l = query[0];
            int r = query[1];
            int k = query[2];
            int v = query[3];
            for (int index = l; index <= r; index += k)
                result[index] = static_cast<int>((1LL * result[index] * v) % modValue);
        }
        return std::accumulate(result.cbegin(), result.cend(), 0, [](int acc, int value){ return acc ^ value; });
    }
};

}

namespace XORAfterRangeMultiplicationQueries1Task
{

TEST(XORAfterRangeMultiplicationQueries1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.xorAfterQueries({1, 1, 1}, {{0, 2, 1, 4}}));
    ASSERT_EQ(31, solution.xorAfterQueries({2, 3, 1, 5, 4}, {{1, 4, 2, 3}, {0, 2, 1, 2}}));
}

}