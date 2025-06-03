#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxCandies(std::vector<int> const &status,
                                 std::vector<int> const &candies,
                                 std::vector<std::vector<int>> const &keys,
                                 std::vector<std::vector<int>> const &containedBoxes,
                                 std::vector<int> const &initialBoxes) const
    {
        std::vector<bool> known(status.size(), false);
        std::vector<bool> open(status.size(), false);
        for (size_t index = 0; index < status.size(); ++index)
            open[index] = (status[index] == 1);
        std::queue<int> boxQueue;
        for (int box : initialBoxes)
        {
            known[box] = true;
            if (open[box])
                boxQueue.emplace(box);
        }
        int totalCandies = 0;
        while (!boxQueue.empty())
        {
            const int current = boxQueue.front();
            totalCandies += candies[current];
            boxQueue.pop();
            for (const int key : keys[current])
            {
                if (known[key] && !open[key])
                    boxQueue.emplace(key);
                open[key] = true;
            }
            for (const int next : containedBoxes[current])
            {
                if (known[next])
                    continue;
                known[next] = true;
                if (open[next])
                    boxQueue.emplace(next);
            }
        }
        return totalCandies;
    }
};

}

namespace MaxCandiesYouCanGetFromBoxesTask
{

TEST(MaxCandiesYouCanGetFromBoxesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(16, solution.maxCandies({1, 0, 1, 0},
                                      {7, 5, 4, 100},
                                      {{}, {}, {1}, {}},
                                      {{1, 2}, {3}, {}, {}},
                                      {0}));
    ASSERT_EQ(6, solution.maxCandies({1, 0, 0, 0, 0, 0},
                                     {1, 1, 1, 1, 1, 1},
                                     {{1, 2, 3, 4, 5}, {}, {}, {}, {}, {}},
                                     {{1, 2, 3, 4, 5}, {}, {}, {}, {}, {}},
                                     {0}));
}

}