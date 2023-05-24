#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxScore(std::vector<int> const &nums1, std::vector<int> const &nums2, int k) const
    {
        long long bestScore = 0;
        std::vector<std::pair<int, int>> pairs;
        for (size_t index = 0; index < nums1.size(); ++index)
            pairs.emplace_back(nums1[index], nums2[index]);
        auto comp = [](std::pair<int, int> const& l, std::pair<int, int> const& r) { return (l.second > r.second) || ((l.second == r.second) && (l.first > r.first)); };
        std::sort(pairs.begin(), pairs.end(), comp);
        long long currentSum = 0;
        std::priority_queue<int, std::vector<int>, std::greater<int>> queue;
        for (std::pair<int, int> const &pair : pairs)
        {
            currentSum += pair.first;
            queue.emplace(pair.first);
            if (queue.size() < static_cast<size_t>(k))
                continue;
            if (queue.size() > static_cast<size_t>(k))
            {
                currentSum -= queue.top();
                queue.pop();
            }
            bestScore = std::max(bestScore, 1LL * pair.second * currentSum);
        }
        return bestScore;
    }
};

}

namespace MaxSubsequenceScoreTask
{

TEST(MaxSubsequenceScoreTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.maxScore({1, 3, 3, 2}, {2, 1, 3, 4}, 3));
    ASSERT_EQ(30, solution.maxScore({4, 2, 3, 1, 1}, {7, 5, 10, 9, 6}, 1));
}

}