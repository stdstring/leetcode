#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution {
public:
    [[nodiscard]] std::vector<int> solveQueries(std::vector<int> const &nums, std::vector<int> const &queries) const
    {
        std::unordered_map<int, std::vector<size_t>> numbers;
        for (size_t index = 0; index < nums.size(); ++index)
            numbers[nums[index]].emplace_back(index);
        std::vector<int> result(queries.size(), -1);
        for (size_t queryIndex = 0; queryIndex < queries.size(); ++queryIndex)
        {
            const int valueIndex = queries[queryIndex];
            const int value = nums[valueIndex];
            std::vector<size_t> const &indexes(numbers[value]);
            if (indexes.size() == 1)
                continue;
            const size_t index = std::distance(indexes.cbegin(), std::ranges::lower_bound(indexes, valueIndex));
            const size_t distanceBack = index > 0 ?
                indexes[index] - indexes[index - 1] :
                nums.size() - indexes.back() + indexes[index];
            const size_t distanceFront = index < indexes.size() - 1 ?
                indexes[index + 1] - indexes[index] :
                nums.size() - indexes[index] + indexes.front();
            result[queryIndex] = static_cast<int>(std::min(distanceBack, distanceFront));
        }
        return result;
    }
};

}

namespace ClosestEqualElementQueriesTask
{

TEST(ClosestEqualElementQueriesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, -1, 3}), solution.solveQueries({1, 3, 1, 4, 1, 3, 2}, {0, 3, 5}));
    ASSERT_EQ(std::vector<int>({-1, -1, -1, -1}), solution.solveQueries({1, 2, 3, 4}, {0, 1, 2, 3}));
}

}