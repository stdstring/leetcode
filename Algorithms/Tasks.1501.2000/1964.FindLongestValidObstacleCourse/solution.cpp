#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> longestObstacleCourseAtEachPosition(std::vector<int> const &obstacles) const
    {
        std::vector<int> lis;
        std::vector<int> result(obstacles.size(), 0);
        for (size_t index = 0; index < obstacles.size(); ++index)
        {
            const size_t lisInsertPos = getInsertPos(lis, obstacles[index]);
            if (lisInsertPos == lis.size())
                lis.emplace_back(obstacles[index]);
            else
                lis[lisInsertPos] = std::min(lis[lisInsertPos], obstacles[index]);
            result[index] = static_cast<int>(lisInsertPos + 1);
        }
        return result;
    }

private:
    [[nodiscard]] size_t getInsertPos(std::vector<int> const &lis, int obstacle) const
    {
        if (lis.empty())
            return 0;
        if (obstacle < lis.front())
            return 0;
        if (obstacle >= lis.back())
            return lis.size();
        size_t left = 0;
        size_t right = lis.size() - 1;
        while (left < right)
        {
            const size_t middle = (left + right) / 2;
            if (lis[middle] <= obstacle)
                left = middle + 1;
            else
                right = middle;
        }
        return left;
    }
};

}

namespace FindLongestValidObstacleCourseTask
{

TEST(FindLongestValidObstacleCourseTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3, 3}), solution.longestObstacleCourseAtEachPosition({1, 2, 3, 2}));
    ASSERT_EQ(std::vector<int>({1, 2, 1}), solution.longestObstacleCourseAtEachPosition({2, 2, 1}));
    ASSERT_EQ(std::vector<int>({1, 1, 2, 3, 2, 2}), solution.longestObstacleCourseAtEachPosition({3, 1, 5, 6, 4, 2}));
}

TEST(FindLongestValidObstacleCourseTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 1, 2, 3, 2, 3, 4, 5, 3, 5}), solution.longestObstacleCourseAtEachPosition({5, 1, 5, 5, 1, 3, 4, 5, 1, 4}));
    ASSERT_EQ(std::vector<int>({1, 1, 2, 2, 1, 2, 3, 4, 4, 4}), solution.longestObstacleCourseAtEachPosition({5, 2, 5, 4, 1, 1, 1, 5, 3, 1}));
}

}