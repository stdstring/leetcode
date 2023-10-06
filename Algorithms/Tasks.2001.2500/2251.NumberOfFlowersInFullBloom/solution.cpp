#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> fullBloomFlowers(std::vector<std::vector<int>> const &flowers, std::vector<int> const &people) const
    {
        // time, increasing/decreasing count of bloom flowers
        std::vector<std::pair<int, int>> events;
        events.reserve(2 * flowers.size());
        for (std::vector<int> const &flower : flowers)
        {
            events.emplace_back(flower[0], +1);
            events.emplace_back(flower[1] + 1, -1);
        }
        std::ranges::sort(events, [](std::pair<int, int> const& l, std::pair<int, int> const& r) { return l.first < r.first; });
        std::vector<std::pair<int, int>> bloomFlowers;
        bloomFlowers.emplace_back(events.front().first, 0);
        for (std::pair<int, int> const &event : events)
        {
            if (bloomFlowers.back().first != event.first)
                bloomFlowers.emplace_back(event.first, bloomFlowers.back().second);
            bloomFlowers.back().second += event.second;
        }
        std::vector<int> answers(people.size(), 0);
        for (size_t index = 0; index < people.size(); ++index)
        {
            if (people[index] < bloomFlowers.front().first)
                continue;
            if (people[index] == bloomFlowers.front().first)
            {
                answers[index] = bloomFlowers.front().second;
                continue;
            }
            if (people[index] >= bloomFlowers.back().first)
                continue;
            answers[index] = findBloomFlowers(bloomFlowers, people[index]);
        }
        return answers;
    }

private:
    [[nodiscard]] int findBloomFlowers(std::vector<std::pair<int, int>> const &bloomFlowers, int time) const
    {
        size_t left = 0;
        size_t right = bloomFlowers.size() - 1;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            if (bloomFlowers[middle].first == time)
                return bloomFlowers[middle].second;
            (bloomFlowers[middle].first < time ? left : right) = middle;
        }
        return bloomFlowers[bloomFlowers[right].first == time ? right : left].second;
    }
};

}

namespace NumberOfFlowersInFullBloomTask
{

TEST(NumberOfFlowersInFullBloomTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 2, 2}), solution.fullBloomFlowers({{1, 6}, {3, 7}, {9, 12}, {4, 13}}, {2, 3, 7, 11}));
    ASSERT_EQ(std::vector<int>({2, 2, 1}), solution.fullBloomFlowers({{1, 10}, {3, 3}}, {3, 3, 2}));
}

}