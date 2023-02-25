#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> construct2DArray(std::vector<int> const &original, int m, int n) const
    {
        const size_t expectedSize = 1ULL * m * n;
        if (expectedSize != original.size())
            return {};
        std::vector<std::vector<int>> result(m, std::vector<int>(n, 0));
        for (size_t index = 0; index < original.size(); ++index)
            result[index / n][index % n] = original[index];
        return result;
    }
};

}

namespace Convert1DArrayInto2DArrayTask
{

TEST(Convert1DArrayInto2DArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2}, {3, 4}}), solution.construct2DArray({1, 2, 3, 4}, 2, 2));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 3}}), solution.construct2DArray({1, 2, 3}, 1, 3));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.construct2DArray({1, 2}, 1, 1));
}

}