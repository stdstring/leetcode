#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumRounds(std::vector<int> const &tasks) const
    {
        std::unordered_map<int, size_t> difficultyMap;
        for (int task : tasks)
            ++difficultyMap[task];
        size_t roundCount = 0;
        for (auto [_, count] : difficultyMap)
        {
            if (count == 1)
                return -1;
            if (count % 2 == 1)
            {
                count -= 3;
                ++roundCount;
            }
            roundCount += 2 * (count / 6) + (count % 6) / 2;
        }
        return static_cast<int>(roundCount);
    }
};

}

namespace MinRoundsCompleteAllTasksTask
{

TEST(MinRoundsCompleteAllTasksTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minimumRounds({2, 2, 3, 3, 2, 4, 4, 4, 4, 4}));
    ASSERT_EQ(-1, solution.minimumRounds({2, 3, 3}));
}

}