#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long matrixSumQueries(int n, std::vector<std::vector<int>> const &queries) const
    {
        constexpr int rowType = 0;
        constexpr int columnType = 1;
        std::vector<int> objects(2ULL * n, -1);
        std::vector<std::pair<int, int>> times(queries.size(), std::pair<int, int>(-1, -1));
        for (size_t queryIndex = 0; queryIndex < queries.size(); ++queryIndex)
        {
            const int type = queries[queryIndex][0];
            const int index = queries[queryIndex][1];
            const int value = queries[queryIndex][2];
            const int object = n * type + index;
            const int time = static_cast<int>(queryIndex);
            if (objects[object] != -1)
                times[objects[object]].first = -1;
            objects[object] = time;
            times[objects[object]].first = object;
            times[objects[object]].second = value;
        }
        long long result = 0;
        int processedRows = 0;
        int processedColumns = 0;
        for (auto iterator = times.crbegin(); iterator != times.crend(); ++iterator)
        {
            if (iterator->first == -1)
                continue;
            const int type = iterator->first / n;
            const int value = iterator->second;
            if (type == rowType)
            {
                result += 1LL * value * (n - processedColumns);
                ++processedRows;
            }
            else if (type == columnType)
            {
                result += 1LL * value * (n - processedRows);
                ++processedColumns;
            }
        }
        return result;
    }
};

}

namespace SumMatrixAfterQueriesTask
{

TEST(SumMatrixAfterQueriesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(23, solution.matrixSumQueries(3, {{0, 0, 1}, {1, 2, 2}, {0, 2, 3}, {1, 0, 4}}));
    ASSERT_EQ(17, solution.matrixSumQueries(3, {{0, 0, 4}, {0, 1, 2}, {1, 0, 1}, {0, 2, 3}, {1, 2, 1}}));
}

}