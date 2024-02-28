#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> countServers(int n, std::vector<std::vector<int>> const &logs, int x, std::vector<int> const &queries) const
    {
        std::vector<std::vector<int>> sortedLogs(logs);
        std::ranges::sort(sortedLogs, [](std::vector<int> const &l, std::vector<int> const &r) { return (l[1] < r[1]); });
        std::vector<size_t> queryIndices(queries.size(), 0);
        std::iota(queryIndices.begin(), queryIndices.end(), 0);
        std::ranges::sort(queryIndices, [&queries](size_t l, size_t r) { return queries[l] < queries[r]; });
        std::vector<int> answers(queries.size(), 0);
        size_t windowStart = 0;
        size_t windowFinish = 0;
        std::unordered_map<int, size_t> windowData;
        for (const size_t queryIndex : queryIndices)
        {
            const int queryTimeLeft = queries[queryIndex] - x;
            const int queryTimeRight = queries[queryIndex];
            while ((windowFinish < sortedLogs.size()) && (sortedLogs[windowFinish][1] <= queryTimeRight))
            {
                ++windowData[sortedLogs[windowFinish][0]];
                ++windowFinish;
            }
            while ((windowStart < sortedLogs.size()) && (sortedLogs[windowStart][1] < queryTimeLeft))
            {
                const auto iterator = windowData.find(sortedLogs[windowStart][0]);
                --iterator->second;
                if (iterator->second == 0)
                    windowData.erase(iterator);
                ++windowStart;
            }
            answers[queryIndex] = n - static_cast<int>(windowData.size());
        }
        return answers;
    }
};

}

namespace CountZeroRequestServersTask
{

TEST(CountZeroRequestServersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2}), solution.countServers(3, {{1, 3}, {2, 6}, {1, 5}}, 5, {10, 11}));
    ASSERT_EQ(std::vector<int>({0, 1}), solution.countServers(3, {{2, 4}, {2, 1}, {1, 2}, {3, 1}}, 2, {3, 4}));
}

}