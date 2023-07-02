#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumRequests(int n, std::vector<std::vector<int>> const &requests) const
    {
        const int maskCount = 1 << requests.size();
        int bestRequestCount = 0;
        for (int mask = 1; mask < maskCount; ++mask)
            bestRequestCount = std::max(bestRequestCount, applyRequestsSubset(n, requests, mask));
        return bestRequestCount;
    }

private:
    [[nodiscard]] int applyRequestsSubset(int n, std::vector<std::vector<int>> const &requests, int mask) const
    {
        int subsetCount = 0;
        std::vector<int> balance(n, 0);
        for (size_t index = 0; index < requests.size(); ++index)
        {
            if ((mask & (1 << index)) == 0)
                continue;
            ++subsetCount;
            --balance[requests[index][0]];
            ++balance[requests[index][1]];
        }
        for (const int value : balance)
        {
            if (value != 0)
                return 0;
        }
        return subsetCount;
    }
};

}

namespace MaxNumberAchievableTransferRequestsTask
{

TEST(MaxNumberAchievableTransferRequestsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maximumRequests(5, {{0, 1}, {1, 0}, {0, 1}, {1, 2}, {2, 0}, {3, 4}}));
    ASSERT_EQ(3, solution.maximumRequests(3, {{0, 0}, {1, 2}, {2, 1}}));
    ASSERT_EQ(4, solution.maximumRequests(4, {{0, 3}, {3, 1}, {1, 2}, {2, 0}}));
}

}