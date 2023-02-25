#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findMaximizedCapital(int k, int w, std::vector<int> const &profits, std::vector<int> const &capital) const
    {
        std::vector<size_t> indices(capital.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&capital](size_t left, size_t right){ return capital[left] < capital[right]; });
        int totalCapital = w;
        size_t currentIndex = 0;
        std::priority_queue<int> profitQueue;
        for (int project = 0; project < k; ++project)
        {
            for (;(currentIndex < indices.size()) && (capital[indices[currentIndex]] <= totalCapital); ++currentIndex)
                profitQueue.push(profits[indices[currentIndex]]);
            if (profitQueue.empty())
                break;
            totalCapital += profitQueue.top();
            profitQueue.pop();
        }
        return totalCapital;
    }
};

}

namespace IPOTask
{

TEST(IPOTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.findMaximizedCapital(2, 0, {1, 2, 3}, {0, 1, 1}));
    ASSERT_EQ(6, solution.findMaximizedCapital(3, 0, {1, 2, 3}, {0, 1, 2}));
}

}