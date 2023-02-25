#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long totalCost(std::vector<int> const &costs, int k, int candidates) const
    {
        typedef std::pair<int, size_t> CandidateData;
        auto cmp = [](CandidateData const &l, CandidateData const &r) { return (l.first > r.first) || ((l.first == r.first) && (l.second > r.second)); };
        std::priority_queue<CandidateData, std::vector<CandidateData>, decltype(cmp)> queue(cmp);
        size_t left = 0;
        size_t right = costs.size() - 1;
        if (2ULL * candidates >= costs.size())
        {
            for (size_t index = 0; index < costs.size(); ++index)
                queue.emplace(costs[index], index);
            left = costs.size() - 1;
            right = 0;
        }
        else
        {
            for (;left < static_cast<size_t>(candidates); ++left)
                queue.emplace(costs[left], left);
            for (;right >= costs.size() - candidates; --right)
                queue.emplace(costs[right], right);
        }
        long long cost = 0;
        for (size_t worker = 1; worker <= static_cast<size_t>(k); ++worker)
        {
            const CandidateData candidate(queue.top());
            queue.pop();
            cost += candidate.first;
            if (left <= right)
            {
                if (candidate.second >= right)
                {
                    queue.emplace(costs[right], right);
                    --right;
                }
                else
                {
                    queue.emplace(costs[left], left);
                    ++left;
                }
            }
        }
        return cost;
    }
};

}

namespace TotalCostHireKWorkersTask
{

TEST(TotalCostHireKWorkersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(11, solution.totalCost({17, 12, 10, 2, 7, 2, 11, 20, 8}, 3, 4));
    ASSERT_EQ(4, solution.totalCost({1, 2, 4, 1}, 3, 3));
}

}