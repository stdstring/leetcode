#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long putMarbles(std::vector<int> const &weights, int k) const
    {
        const size_t interestedPairCount = k - 1;
        std::vector<long long> pairs;
        for (size_t index = 0; index < weights.size() - 1; ++index)
            pairs.emplace_back(0LL + weights[index] + weights[index + 1]);
        std::ranges::sort(pairs);
        long long minScore = 0;
        for (size_t index = 0; index < interestedPairCount; ++index)
            minScore += pairs[index];
        long long maxScore = 0;
        for (size_t index = 0; index < interestedPairCount; ++index)
            maxScore += pairs[pairs.size() -  1 - index];
        return maxScore - minScore;
    }
};

}

namespace PutMarblesInBagsTask
{

TEST(PutMarblesInBagsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.putMarbles({1, 3, 5, 1}, 2));
    ASSERT_EQ(0, solution.putMarbles({1, 3}, 2));
}

}