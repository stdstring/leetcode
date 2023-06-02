#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumDetonation(std::vector<std::vector<int>> const &bombs) const
    {
        const std::vector<std::vector<size_t>> links(generateLinks(bombs));
        int bestDetonation = 0;
        for (size_t index = 0; index < links.size(); ++index)
            bestDetonation = std::max(bestDetonation, calcDetonationCount(links, index));
        return bestDetonation;
    }

private:
    [[nodiscard]] std::vector<std::vector<size_t>> generateLinks(std::vector<std::vector<int>> const &bombs) const
    {
        std::vector<std::vector<size_t>> links(bombs.size(), std::vector<size_t>());
        for (size_t index1 = 0; index1 < bombs.size(); ++index1)
        {
            const long long x1 = bombs[index1][0];
            const long long y1 = bombs[index1][1];
            const long long r1 = bombs[index1][2];
            for (size_t index2 = index1 + 1; index2 < bombs.size(); ++index2)
            {
                const long long x2 = bombs[index2][0];
                const long long y2 = bombs[index2][1];
                const long long r2 = bombs[index2][2];
                const long long distance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
                if (distance <= (r1 * r1))
                    links[index1].push_back(index2);
                if (distance <= (r2 * r2))
                    links[index2].push_back(index1);
            }
        }
        return links;
    }

    [[nodiscard]] int calcDetonationCount(std::vector<std::vector<size_t>> const &links, size_t init) const
    {
        std::vector<bool> visited(links.size(), false);
        visited[init] = true;
        int detonationCount = 1;
        std::queue<size_t> queue;
        queue.emplace(init);
        while (!queue.empty())
        {
            const size_t current = queue.front();
            queue.pop();
            for (size_t link : links[current])
            {
                if (!visited[link])
                {
                    visited[link] = true;
                    ++detonationCount;
                    queue.emplace(link);
                }
            }
        }
        return detonationCount;
    }
};

}

namespace DetonateMaxBombsTask
{

TEST(DetonateMaxBombsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maximumDetonation({{2, 1, 3}, {6, 1, 4}}));
    ASSERT_EQ(1, solution.maximumDetonation({{1, 1, 5}, {10, 10, 5}}));
    ASSERT_EQ(5, solution.maximumDetonation({{1, 2, 3}, {2, 3, 1}, {3, 4, 2}, {4, 5, 3}, {5, 6, 4}}));
}

TEST(DetonateMaxBombsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.maximumDetonation({{54, 95, 4},
                                             {99, 46, 3},
                                             {29, 21, 3},
                                             {96, 72, 8},
                                             {49, 43, 3},
                                             {11, 20, 3},
                                             {2, 57, 1},
                                             {69, 51, 7},
                                             {97, 1, 10},
                                             {85, 45, 2},
                                             {38, 47, 1},
                                             {83, 75, 3},
                                             {65, 59, 3},
                                             {33, 4, 1},
                                             {32, 10, 2},
                                             {20, 97, 8},
                                             {35, 37, 3}}));
}

}