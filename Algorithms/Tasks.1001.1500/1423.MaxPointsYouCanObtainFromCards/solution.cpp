#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxScore(std::vector<int> const &cardPoints, int k) const
    {
        const int totalSum = std::accumulate(cardPoints.cbegin(), cardPoints.cend(), 0);
        const size_t slidingWindowSize = cardPoints.size() - k;
        int slidingWindowSum = std::accumulate(cardPoints.cbegin(), std::next(cardPoints.cbegin(), static_cast<int>(slidingWindowSize)), 0);
        int maxPoints = totalSum - slidingWindowSum;
        for (size_t index = 1; index <= cardPoints.size() - slidingWindowSize; ++index)
        {
            slidingWindowSum -= cardPoints[index - 1];
            slidingWindowSum += cardPoints[index + slidingWindowSize - 1];
            maxPoints = std::max(maxPoints, totalSum - slidingWindowSum);
        }
        return maxPoints;
    }
};

}

namespace MaxPointsYouCanObtainFromCardsTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.maxScore({1, 2, 3, 4, 5, 6, 1}, 3));
    ASSERT_EQ(4, solution.maxScore({2, 2, 2}, 2));
    ASSERT_EQ(55, solution.maxScore({9, 7, 7, 9, 7, 7, 9}, 7));
}

}
