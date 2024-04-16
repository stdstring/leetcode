#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int miceAndCheese(std::vector<int> const &reward1, std::vector<int> const &reward2, int k) const
    {
        const int totalReward2 = std::accumulate(reward2.cbegin(), reward2.cend(), 0);
        std::vector<size_t> indices(reward1.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        auto comp = [&reward1, &reward2](size_t l, size_t r)
        {
                return (reward1[l] - reward2[l]) > (reward1[r] - reward2[r]);
        };
        std::ranges::sort(indices, comp);
        int result = totalReward2;
        for (size_t index = 0; index < static_cast<size_t>(k); ++index)
            result += reward1[indices[index]] - reward2[indices[index]];
        return result;
    }
};

}

namespace MiceAndCheeseTask
{

TEST(MiceAndCheeseTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.miceAndCheese({1, 1, 3, 4}, {4, 4, 1, 1}, 2));
    ASSERT_EQ(2, solution.miceAndCheese({1, 1}, {1, 1}, 2));
}

}