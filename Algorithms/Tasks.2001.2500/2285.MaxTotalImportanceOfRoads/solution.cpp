#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maximumImportance(int n, std::vector<std::vector<int>> const &roads) const
    {
        std::vector<int> nodesImportance(n, 0);
        for (std::vector<int> const &road : roads)
        {
            ++nodesImportance[road[0]];
            ++nodesImportance[road[1]];
        }
        std::vector<size_t> indices(n, 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::ranges::sort(indices, [&nodesImportance](size_t left, size_t right){ return nodesImportance[left] > nodesImportance[right]; });
        long long result = 0;
        for (size_t index = 0; index < indices.size(); ++index)
        {
            result += static_cast<long long>((indices.size() - index) * nodesImportance[indices[index]]);
        }
        return result;
    }
};

}

namespace MaxTotalImportanceOfRoadsTask
{

TEST(MaxTotalImportanceOfRoadsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(43, solution.maximumImportance(5, {{0, 1}, {1, 2}, {2, 3}, {0, 2}, {1, 3}, {2, 4}}));
    ASSERT_EQ(20, solution.maximumImportance(5, {{0, 3}, {2, 4}, {1, 3}}));
}

}