#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> xorQueries(std::vector<int> const &arr, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<int> prefixXor(arr.size(), 0);
        for (size_t index = 0; index < arr.size(); ++index)
            prefixXor[index] = arr[index] ^ (index > 0 ? prefixXor[index - 1] : 0);
        std::vector<int> result(queries.size(), 0);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            const int from = queries[index][0];
            const int to = queries[index][1];
            result[index] = prefixXor[to] ^ (from > 0 ? prefixXor[from - 1] : 0);
        }
        return result;
    }
};

}

namespace XORQueriesOfSubarrayTask
{

TEST(XORQueriesOfSubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 7, 14, 8}), solution.xorQueries({1, 3, 4, 8}, {{0, 1}, {1, 2}, {0, 3}, {3, 3}}));
    ASSERT_EQ(std::vector<int>({8, 0, 4, 4}), solution.xorQueries({4, 8, 2, 10}, {{2, 3}, {1, 3}, {0, 0}, {0, 3}}));
}

}