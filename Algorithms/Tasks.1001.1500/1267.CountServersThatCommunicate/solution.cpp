#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countServers(std::vector<std::vector<int>> const &grid) const
    {
        typedef std::pair<size_t, size_t> TCoord;
        auto coordHash = [](TCoord const &coord)
        {
            return std::hash<size_t>{}(coord.first) ^ std::hash<size_t>{}(coord.second);
        };
        std::unordered_map<TCoord, bool, decltype(coordHash)> servers(16, coordHash);
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        // prepare
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] == 1)
                    servers.emplace(TCoord(row, column), false);
            }
        }
        // process rows
        for (size_t row = 0; row < rowCount; ++row)
        {
            std::vector<TCoord> rowServers;
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] == 1)
                    rowServers.emplace_back(row, column);
            }
            if (rowServers.size() > 1)
                for (TCoord const &coord : rowServers)
                    servers[coord] = true;
        }
        // process columns
        for (size_t column = 0; column < columnCount; ++column)
        {
            std::vector<TCoord> columnServers;
            for (size_t row = 0; row < rowCount; ++row)
            {
                if (grid[row][column] == 1)
                    columnServers.emplace_back(row, column);
            }
            if (columnServers.size() > 1)
                for (TCoord const &coord : columnServers)
                    servers[coord] = true;
        }
        // count connected servers
        return static_cast<int>(std::ranges::count_if(servers, [](auto const &entry) { return entry.second; }));
    }
};

}

namespace CountServersThatCommunicateTask
{

TEST(CountServersThatCommunicateTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.countServers({{1, 0}, {0, 1}}));
    ASSERT_EQ(3, solution.countServers({{1, 0}, {1, 1}}));
    ASSERT_EQ(4, solution.countServers({{1, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}));
}

TEST(CountServersThatCommunicateTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countServers({{1, 0, 0, 1, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 1, 0}}));
}

}