#include <algorithm>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximizeSquareArea(int m, int n, std::vector<int> const &hFences, std::vector<int> const &vFences) const
    {
        // prepare data
        std::unordered_set<int> hDistances;
        hDistances.insert(m - 1);
        for (size_t start = 0; start < hFences.size(); ++start)
        {
            hDistances.insert(hFences[start] - 1);
            hDistances.insert(m - hFences[start]);
            for (size_t end = 0; end < hFences.size(); ++end)
            {
                if (start == end)
                    continue;
                if (hFences[start] < hFences[end])
                    hDistances.insert(hFences[end] - hFences[start]);
            }
        }
        // calc square area
        unsigned long long maxArea = 0;
        if (hDistances.contains(n - 1))
            maxArea = std::max(maxArea, 1ULL * (n - 1) * (n - 1));
        for (size_t start = 0; start < vFences.size(); ++start)
        {
            if (hDistances.contains(vFences[start] - 1))
                maxArea = std::max(maxArea, 1ULL * (vFences[start] - 1) * (vFences[start] - 1));
            if (hDistances.contains(n - vFences[start]))
                maxArea = std::max(maxArea, 1ULL * (n - vFences[start]) * (n - vFences[start]));
            for (size_t end = 0; end < vFences.size(); ++end)
            {
                if (start == end)
                    continue;
                if ((vFences[start] < vFences[end]) && (hDistances.contains(vFences[end] - vFences[start])))
                    maxArea = std::max(maxArea, 1ULL * (vFences[end] - vFences[start]) * (vFences[end] - vFences[start]));
            }
        }
        constexpr size_t modValue = 1000000007;
        return maxArea == 0 ? -1 : static_cast<int>(maxArea % modValue);
    }
};

}

namespace MaxSquareAreaByRemovingFencesTask
{

TEST(MaxSquareAreaByRemovingFencesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maximizeSquareArea(4, 3, {2, 3}, {2}));
    ASSERT_EQ(-1, solution.maximizeSquareArea(6, 7, {2}, {4}));
}

}